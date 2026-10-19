#include <NKCore/NkTypes.h>
#include <NKLogger/NkLog.h>
#include <NKThreading/NkThread.h>
#include "NKWindow/NKMain.h"

// Pour le test principal : huit fils.
// Pour le test a un seul fil, remplacer 8 par 1, recompiler et lancer,
// puis remettre 8 pour les essais suivants.
constexpr nkentseu::int32 NombreDeFils = 8;
constexpr nkentseu::int32 IncrementationsParFil = 1000000;

int nkmain(nkentseu::NkEntryState const& state)
{
    nkentseu::int32 compteur = 0;
    nkentseu::threading::NkThread fils[NombreDeFils];
    bool creationIncomplete = false;

    logger.Info("Exercice 2 : La course provoquee");
    logger.Info("Nombre de fils : {0}", NombreDeFils);
    logger.Info("Incrementations par fil : {0}", IncrementationsParFil);

    for (nkentseu::int32 i = 0; i < NombreDeFils; ++i) {
        fils[i] = nkentseu::threading::NkThread([&compteur](void*) {
            for (nkentseu::int32 j = 0; j < IncrementationsParFil; ++j) {
                compteur += 1; // Course volontaire : ne pas ajouter de protection.
            }
        });

        if (!fils[i].Joinable()) {
            logger.Error("Le fil {0} n'a pas pu demarrer.", i + 1);
            creationIncomplete = true;
        }
    }

    // Attendre la fin de chaque fil qui a bien demarre.
    for (nkentseu::int32 i = 0; i < NombreDeFils; ++i) {
        if (fils[i].Joinable()) {
            fils[i].Join();
        }
    }

    if (creationIncomplete) {
        logger.Error("Le test est incomplet : tous les fils n'ont pas demarre.");
        return 1;
    }

    const nkentseu::int32 totalAttendu =
        NombreDeFils * IncrementationsParFil;

    logger.Info("Total observe : {0}", compteur);
    logger.Info("Total attendu : {0}", totalAttendu);
    logger.Info("Ecart observe : {0}", totalAttendu - compteur);

    return 0;
}