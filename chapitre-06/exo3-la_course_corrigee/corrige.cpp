// Chapitre 06 — Exercice 3 : La course corrigée
//
// On effectue le même travail avec quatre stratégies, puis on compare
// les durées en Release. La version sans protection est volontairement
// incorrecte : elle sert de point de comparaison, pas de modèle à suivre.

#include <NKCore/NkTypes.h>
#include <NKCore/NkAtomic.h>
#include <NKThreading/NkMutex.h>
#include <NKThreading/NkScopedLock.h>
#include <NKThreading/NkThread.h>
#include <NKTime/NkChrono.h>
#include <NKLogger/NkLog.h>
#include "NKWindow/NKMain.h"

using namespace nkentseu;

constexpr int32 NombreDeFils = 8;
constexpr int32 IncrementationsParFil = 1000000;
constexpr int32 NombreDeMesures = 3;

struct ResultatMesure {
    int32 total;
    float64 tempsMs;
    bool complet;
};

using FonctionMesure = ResultatMesure (*)();

// On attend chaque fil qui a réellement démarré. Si Joinable() est faux
// dès le départ, la création a échoué et cette mesure n'est pas complète.
bool JoindreFils(threading::NkThread fils[])
{
    bool complet = true;

    for (int32 i = 0; i < NombreDeFils; ++i) {
        if (fils[i].Joinable()) {
            fils[i].Join();
        } else {
            complet = false;
        }
    }

    return complet;
}

ResultatMesure MesurerSansProtection()
{
    int32 compteur = 0;
    threading::NkThread fils[NombreDeFils];
    NkChrono chrono; // Le temps inclut la création, le travail et les Join().

    for (int32 i = 0; i < NombreDeFils; ++i) {
        fils[i] = threading::NkThread([&compteur](void*) {
            for (int32 j = 0; j < IncrementationsParFil; ++j) {
                ++compteur; // Course volontaire : tous les fils écrivent ici.
            }
        });
    }

    const bool complet = JoindreFils(fils);
    return { compteur, chrono.Elapsed().milliseconds, complet };
}

ResultatMesure MesurerMutex()
{
    int32 compteur = 0;
    threading::NkMutex mutex;
    threading::NkThread fils[NombreDeFils];
    NkChrono chrono;

    for (int32 i = 0; i < NombreDeFils; ++i) {
        fils[i] = threading::NkThread([&compteur, &mutex](void*) {
            for (int32 j = 0; j < IncrementationsParFil; ++j) {
                // Le verrou ne couvre que l'incrément, pas toute la boucle.
                {
                    threading::NkScopedLock<threading::NkMutex> verrou(mutex);
                    ++compteur;
                }
            }
        });
    }

    const bool complet = JoindreFils(fils);
    return { compteur, chrono.Elapsed().milliseconds, complet };
}

ResultatMesure MesurerAtomique()
{
    NkAtomicInt compteur(0);
    threading::NkThread fils[NombreDeFils];
    NkChrono chrono;

    for (int32 i = 0; i < NombreDeFils; ++i) {
        fils[i] = threading::NkThread([&compteur](void*) {
            for (int32 j = 0; j < IncrementationsParFil; ++j) {
                compteur.FetchAdd(1); // Incrémentation atomique du compteur partagé.
            }
        });
    }

    const bool complet = JoindreFils(fils);
    return { compteur.Load(), chrono.Elapsed().milliseconds, complet };
}

ResultatMesure MesurerLocal()
{
    int32 totauxLocaux[NombreDeFils] = {};
    threading::NkThread fils[NombreDeFils];
    NkChrono chrono;

    for (int32 i = 0; i < NombreDeFils; ++i) {
        fils[i] = threading::NkThread([&totauxLocaux, i](void*) {
            // Chaque fil travaille sur sa propre variable : aucun compteur partagé.
            int32 compteurLocal = 0;
            for (int32 j = 0; j < IncrementationsParFil; ++j) {
                ++compteurLocal;
            }
            totauxLocaux[i] = compteurLocal;
        });
    }

    const bool complet = JoindreFils(fils);

    // Les résultats locaux ne sont lus qu'après la fin de tous les fils.
    int32 total = 0;
    for (int32 i = 0; i < NombreDeFils; ++i) {
        total += totauxLocaux[i];
    }

    return { total, chrono.Elapsed().milliseconds, complet };
}

// Avec trois mesures, la médiane est simplement la valeur du milieu.
float64 Mediane(float64 a, float64 b, float64 c)
{
    if (a > b) { const float64 t = a; a = b; b = t; }
    if (b > c) { const float64 t = b; b = c; c = t; }
    if (a > b) { const float64 t = a; a = b; b = t; }
    return b;
}

void MesurerVersion(const char* nom, FonctionMesure mesurer)
{
    float64 temps[NombreDeMesures] = {};
    int32 dernierTotal = 0;

    logger.Info("--- {0} ---", nom);

    for (int32 i = 0; i < NombreDeMesures; ++i) {
        const ResultatMesure resultat = mesurer();
        temps[i] = resultat.tempsMs;
        dernierTotal = resultat.total;

        logger.Info("Essai {0} : total = {1}, temps = {2} ms",
                    i + 1, resultat.total, resultat.tempsMs);

        if (!resultat.complet) {
            logger.Error("La mesure {0} est incomplète : un fil n'a pas démarré.", nom);
        }
    }

    logger.Info("{0} : dernier total = {1}, temps médian = {2} ms",
                nom, dernierTotal, Mediane(temps[0], temps[1], temps[2]));
}

int nkmain()
{
    logger.Info("Exercice 3 : La course corrigée");
    logger.Info("Nombre de fils : {0}", NombreDeFils);
    logger.Info("Incrémentations par fil : {0}", IncrementationsParFil);
    logger.Info("Total attendu pour les versions correctes : {0}",
                NombreDeFils * IncrementationsParFil);
    logger.Info("Lancer en Release pour comparer les performances.");

    MesurerVersion("Sans protection", MesurerSansProtection);
    MesurerVersion("Mutex", MesurerMutex);
    MesurerVersion("Atomique", MesurerAtomique);
    MesurerVersion("Local", MesurerLocal);

    logger.Info("Mesures terminées. Consulter logs/app.log pour les résultats.");
    return 0;
}
