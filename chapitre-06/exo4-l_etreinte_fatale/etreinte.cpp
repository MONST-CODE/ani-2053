// Chapitre 06 — Exercice 4 : L'etreinte fatale
//
// La version qui se fige est gardee en commentaire pour l'experience au
// debogueur. Dans la version executable, les deux fils prennent les verrous
// dans le meme ordre : m1, puis m2.

#include <NKLogger/NkLog.h>
#include <NKThreading/NkMutex.h>
#include <NKThreading/NkScopedLock.h>
#include <NKThreading/NkThread.h>
#include <NKTime/NkChrono.h>

using nkentseu::NkChrono;
using nkentseu::threading::NkMutex;
using nkentseu::threading::NkScopedLock;
using nkentseu::threading::NkThread;

// Version qui se fige — activez-la temporairement pour l'observer au debogueur.
// Pour la reproduire, de-commentez la fonction ci-dessous et commentez celle
// qui est executable plus bas. Gardez les lignes telles quelles pour conserver
// les numeros indiques dans le compte rendu.
//
//
// int nkmain()
// {
//     NkMutex m1;
//     NkMutex m2;
//
//     logger.Info("Version bloquee : lancement des deux fils.");
//
//     NkThread a([&m1, &m2](void*) {
//         NkScopedLock<NkMutex> verrouM1(m1);
//         NkChrono::SleepMilliseconds(100);
//         NkScopedLock<NkMutex> verrouM2(m2); // A attend m2 ici (ligne 34)
//     });
//
//     NkThread b([&m1, &m2](void*) {
//         NkScopedLock<NkMutex> verrouM2(m2);
//         NkChrono::SleepMilliseconds(100);
//         NkScopedLock<NkMutex> verrouM1(m1); // B attend m1 ici (ligne 40)
//     });
//
//     a.Join();
//     b.Join();
//     return 0;
// }
//
int nkmain()
{
    NkMutex m1;
    NkMutex m2;

    logger.Info("Exercice 4 : l'etreinte fatale");
    logger.Info("Les deux fils vont prendre les verrous dans le meme ordre.");

    NkThread a([&m1, &m2](void*) {
        NkScopedLock<NkMutex> verrouM1(m1);
        NkChrono::SleepMilliseconds(100);
        NkScopedLock<NkMutex> verrouM2(m2);
    });

    NkThread b([&m1, &m2](void*) {
        // B respecte le meme ordre que A : d'abord m1, ensuite m2.
        NkScopedLock<NkMutex> verrouM1(m1);
        NkChrono::SleepMilliseconds(100);
        NkScopedLock<NkMutex> verrouM2(m2);
    });

    // Join attend la fin de chaque fil avant de detruire les mutex.
    a.Join();
    b.Join();

    logger.Info("Les deux fils ont termine : le blocage est corrige.");
    return 0;
}
