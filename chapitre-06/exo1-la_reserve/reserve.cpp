// Chapitre 06 — Exercice 1 : La réserve
// Compare une NkThreadPool réutilisée à la création de 200 NkThread.
// Les durées sont mesurées avec NkChrono, et les résultats sont conservés
// puis affichés afin que le travail reste observable en configuration Release.

#include <NKThreading/NkThread.h>
#include <NKThreading/NkThreadPool.h>
#include <NKTime/NkChrono.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iostream>

namespace {

using nkentseu::NkChrono;
using nkentseu::threading::NkThread;
using nkentseu::threading::NkThreadPool;

constexpr std::size_t TaskCount = 200;
constexpr std::size_t ValuesPerTask = 1000;
constexpr std::size_t MeasurementCount = 3;
constexpr unsigned ShortTaskPasses = 1;
constexpr unsigned LongTaskPasses = 100;

using Checksum = std::uint64_t;

struct TrialResult {
    double milliseconds;
    Checksum checksum;
};

struct MeasurementSeries {
    TrialResult trials[MeasurementCount];
};

// Chaque tâche additionne le même tableau en lecture seule. Le tableau est
// rempli à l'exécution, avant le chronométrage : sa somme ne peut pas être
// remplacée à la compilation par une constante connue à l'avance.
Checksum SumValues(const int* values,
                  std::size_t valueCount,
                  unsigned passes) noexcept {
    Checksum sum = 0;

    for (unsigned pass = 0; pass < passes; ++pass) {
        // Chaque passe parcourt bien tous les entiers, mais en commençant à
        // un décalage différent. Cela conserve la même somme tout en évitant
        // qu'une optimisation ne réduise facilement la répétition à un produit.
        const std::size_t offset = static_cast<std::size_t>(pass) % valueCount;

        for (std::size_t index = 0; index < valueCount; ++index) {
            std::size_t sourceIndex = offset + index;
            if (sourceIndex >= valueCount) {
                sourceIndex -= valueCount;
            }
            sum += static_cast<Checksum>(values[sourceIndex]);
        }
    }

    return sum;
}

Checksum SumResults(const Checksum* results, std::size_t count) noexcept {
    Checksum total = 0;

    for (std::size_t index = 0; index < count; ++index) {
        total += results[index];
    }

    return total;
}

double AverageMilliseconds(const MeasurementSeries& series) noexcept {
    double total = 0.0;

    for (std::size_t index = 0; index < MeasurementCount; ++index) {
        total += series.trials[index].milliseconds;
    }

    return total / static_cast<double>(MeasurementCount);
}

bool HasConsistentChecksums(const MeasurementSeries& series) noexcept {
    const Checksum expected = series.trials[0].checksum;

    for (std::size_t index = 1; index < MeasurementCount; ++index) {
        if (series.trials[index].checksum != expected) {
            return false;
        }
    }

    return true;
}

// Le pool est créé hors du chronométrage et réutilisé pour les six séries :
// on mesure le coût de soumission des tâches et de Join(), pas son démarrage
// ponctuel. Chaque tâche écrit dans une case distincte du tableau de résultats.
void MeasureWithPool(NkThreadPool& pool,
                     const int* values,
                     unsigned passes,
                     MeasurementSeries& measurements) {
    for (std::size_t trial = 0; trial < MeasurementCount; ++trial) {
        Checksum results[TaskCount] = {};
        Checksum* const resultSlots = results;

        NkChrono chrono;

        for (std::size_t taskIndex = 0; taskIndex < TaskCount; ++taskIndex) {
            pool.Enqueue([values, resultSlots, taskIndex, passes]() {
                resultSlots[taskIndex] =
                    SumValues(values, ValuesPerTask, passes);
            });
        }

        // Join() attend la fin de toutes les tâches qui viennent d'être soumises.
        pool.Join();

        measurements.trials[trial].milliseconds = chrono.Elapsed().milliseconds;
        measurements.trials[trial].checksum = SumResults(results, TaskCount);
    }
}

// Ici, la création des 200 threads et leur Join() sont tous deux chronométrés.
// Un tableau de NkThread est réutilisé entre les essais, mais chaque case reçoit
// un nouveau thread natif au cours de chaque essai.
bool MeasureWithIndividualThreads(const int* values,
                                  unsigned passes,
                                  MeasurementSeries& measurements) {
    for (std::size_t trial = 0; trial < MeasurementCount; ++trial) {
        NkThread workers[TaskCount];
        bool started[TaskCount] = {};
        Checksum results[TaskCount] = {};
        Checksum* const resultSlots = results;
        bool allThreadsStarted = true;

        NkChrono chrono;

        for (std::size_t taskIndex = 0; taskIndex < TaskCount; ++taskIndex) {
            workers[taskIndex] = NkThread([values, resultSlots, taskIndex, passes](void*) {
                resultSlots[taskIndex] =
                    SumValues(values, ValuesPerTask, passes);
            });

            // NkThread gère les échecs de création sans exception ; Joinable()
            // permet de ne joindre que les threads qui ont réellement démarré.
            started[taskIndex] = workers[taskIndex].Joinable();
            if (!started[taskIndex]) {
                allThreadsStarted = false;
            }
        }

        for (std::size_t taskIndex = 0; taskIndex < TaskCount; ++taskIndex) {
            if (started[taskIndex]) {
                workers[taskIndex].Join();
            }
        }

        const double elapsedMilliseconds = chrono.Elapsed().milliseconds;

        if (!allThreadsStarted) {
            std::fprintf(stderr,
                         "Erreur : au moins un des %zu NkThread n'a pas pu démarrer.\n",
                         TaskCount);
            return false;
        }

        measurements.trials[trial].milliseconds = elapsedMilliseconds;
        measurements.trials[trial].checksum = SumResults(results, TaskCount);
    }

    return true;
}

void PrintThreeMeasurements(const char* label,
                            const MeasurementSeries& series) noexcept {
    std::printf("%s : %.3f ms, %.3f ms, %.3f ms\n",
                label,
                series.trials[0].milliseconds,
                series.trials[1].milliseconds,
                series.trials[2].milliseconds);
}

void PrintLongMeasurements(const char* label,
                           const MeasurementSeries& series) noexcept {
    std::printf("Détail tâche longue — %s : %.3f ms, %.3f ms, %.3f ms\n",
                label,
                series.trials[0].milliseconds,
                series.trials[1].milliseconds,
                series.trials[2].milliseconds);
}

void FillInput(int* values, std::size_t count) noexcept {
    // NkChrono fournit une graine lue à l'exécution ; les valeurs restent
    // identiques pendant tout le benchmark et sont partagées en lecture seule.
    Checksum seed = static_cast<Checksum>(NkChrono::Now().nanoseconds);
    if (seed == 0) {
        seed = 0x9E3779B97F4A7C15ULL;
    }

    for (std::size_t index = 0; index < count; ++index) {
        seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;
        values[index] = static_cast<int>(((seed >> 32) % 1000ULL) + 1ULL);
    }
}

} // namespace

int main() {
    int values[ValuesPerTask] = {};
    FillInput(values, ValuesPerTask);

    MeasurementSeries poolShort{};
    MeasurementSeries poolLong{};
    MeasurementSeries threadsShort{};
    MeasurementSeries threadsLong{};
    unsigned workerCount = 0;

    // Conserver le pool entre les essais amortit son démarrage : c'est le
    // comportement attendu d'une réserve déjà prête à recevoir du travail.
    {
        NkThreadPool pool;
        workerCount = static_cast<unsigned>(pool.GetNumWorkers());

        MeasureWithPool(pool, values, ShortTaskPasses, poolShort);
        MeasureWithPool(pool, values, LongTaskPasses, poolLong);
    } // Tous les travaux sont joints ; le pool peut ensuite libérer ses ouvriers.

    if (!MeasureWithIndividualThreads(values, ShortTaskPasses, threadsShort) ||
        !MeasureWithIndividualThreads(values, LongTaskPasses, threadsLong)) {
        return 1;
    }

    if (!HasConsistentChecksums(poolShort) ||
        !HasConsistentChecksums(poolLong) ||
        !HasConsistentChecksums(threadsShort) ||
        !HasConsistentChecksums(threadsLong) ||
        poolShort.trials[0].checksum != threadsShort.trials[0].checksum ||
        poolLong.trials[0].checksum != threadsLong.trials[0].checksum) {
        std::fprintf(stderr,
                     "Erreur : les résultats diffèrent entre les deux méthodes.\n");
        return 2;
    }

    std::printf("Tâche : %zu tâches ; chacune additionne %zu entiers. "
                "La tâche longue répète la somme %u fois.\n",
                TaskCount, ValuesPerTask, LongTaskPasses);
    PrintThreeMeasurements("Réserve", poolShort);
    PrintThreeMeasurements("Fils", threadsShort);
    std::printf("Ouvriers : %u\n", workerCount);
    std::printf("Tâche longue : Réserve (moyenne de 3) = %.3f ms ; "
                "Fils (moyenne de 3) = %.3f ms\n",
                AverageMilliseconds(poolLong),
                AverageMilliseconds(threadsLong));

    // Ces valeurs rendent le résultat du calcul observable, y compris en Release.
    std::printf("Somme de contrôle (tâche courte) : réserve = %llu ; fils = %llu\n",
                static_cast<unsigned long long>(poolShort.trials[0].checksum),
                static_cast<unsigned long long>(threadsShort.trials[0].checksum));
    std::printf("Somme de contrôle (tâche longue) : réserve = %llu ; fils = %llu\n",
                static_cast<unsigned long long>(poolLong.trials[0].checksum),
                static_cast<unsigned long long>(threadsLong.trials[0].checksum));

    PrintLongMeasurements("Réserve", poolLong);
    PrintLongMeasurements("Fils", threadsLong);

    std::cout<<"Pourquoi : pour les tâches courtes, le coût de création de 200 fils "
                <<"peut dominer le calcul. La réserve réutilise ses ouvriers et évite "
                <<"de recréer un thread pour chaque tâche. Quand le travail est 100 fois "
                <<"plus long, le calcul utile pèse davantage dans le temps total : le "
                <<"coût de création devient proportionnellement moins important.\n";

    return 0;
}
