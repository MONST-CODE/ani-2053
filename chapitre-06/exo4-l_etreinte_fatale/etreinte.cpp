// Chapitre 06 — Exercice 4 : L'étreinte fatale
//
// La version bloquée est conservée en commentaire pour le débogueur.
// Dans la version corrigée, les deux fils prennent les verrous dans le même ordre.
#include <ctime>
#define time(...) (std::time(__VA_ARGS__))
#include "NKWindow/NKMain.h"
#undef time
#include <NKLogger/NkLog.h>
#include <NKThreading/NkMutex.h>
#include <NKThreading/NkScopedLock.h>
#include <NKThreading/NkThread.h>
#include <NKTime/NkChrono.h>


using nkentseu::NkChrono;
using nkentseu::threading::NkMutex;
using nkentseu::threading::NkThread;

// Version qui se fige : elle montre l'interblocage entre les deux fils.
// Elle reste commentée pour que seule la version corrigée soit compilée.
// A prend m1 puis attend m2 ; B prend m2 puis attend m1.
// Les attentes de 100 ms donnent aux deux fils le temps de prendre leur premier verrou.
// Les deux fils sont ensuite joints, comme dans la version corrigée.
// Le using de NkScopedLock est volontairement absent : le kit définit déjà
// un alias global portant ce nom. On qualifie donc directement le type ci-dessous.
/*
int nkmain()
{
    NkMutex m1;
    NkMutex m2;

    logger.Info("Version bloquée : lancement des deux fils.");

    NkThread a([&m1, &m2](void*) {
        nkentseu::threading::NkScopedLock<NkMutex> verrouM1(m1);
        NkChrono::SleepMilliseconds(100);
        nkentseu::threading::NkScopedLock<NkMutex> verrouM2(m2); // A attend m2 ici (ligne 34)
    });

    NkThread b([&m1, &m2](void*) {
        nkentseu::threading::NkScopedLock<NkMutex> verrouM2(m2);
        NkChrono::SleepMilliseconds(100);
        nkentseu::threading::NkScopedLock<NkMutex> verrouM1(m1); // B attend m1 ici (ligne 40)
    });

    a.Join();
    b.Join();
    return 0;
}
*/

// Version corrigée : les deux fils prennent m1, puis m2.
int nkmain(nkentseu::NkEntryState const& state)
{
    NkMutex m1;
    NkMutex m2;

    logger.Info("Exercice 4 : l'etreinte fatale");
    logger.Info("Les deux fils prennent les verrous dans le meme ordre.");

    NkThread a([&m1, &m2](void*) {
        nkentseu::threading::NkScopedLock<NkMutex> verrouM1(m1);
        NkChrono::SleepMilliseconds(100);
        nkentseu::threading::NkScopedLock<NkMutex> verrouM2(m2);
    });

    NkThread b([&m1, &m2](void*) {
        // Même ordre que A : d'abord m1, puis m2.
        nkentseu::threading::NkScopedLock<NkMutex> verrouM1(m1);
        NkChrono::SleepMilliseconds(100);
        nkentseu::threading::NkScopedLock<NkMutex> verrouM2(m2);
    });

    // Join attend la fin des deux fils avant la destruction des mutex.
    a.Join();
    b.Join();

    logger.Info("Les deux fils ont termine : le blocage est corrige.");
    return 0;
}
