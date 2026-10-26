
#include "NKCanvas/App/NkCanvasApp.h"
#include "NKLogger/NkLog.h"

#include <cstdint>
#include <fstream>

// Essai 1 : 0 = plafond 60 ; 1 = sans plafond
#define SONDE_SANS_PLAFOND 0

// Essai 2 : 0 = journalisation active ; 1 = sans la ligne de journalisation
#define SONDE_SANS_LIGNE 0

namespace {

class Sonde final : public nkentseu::renderer::NkCanvasApp {
public:
    Sonde() {
        Config().title = "Exercice 6 - La sonde qui compte";
        Config().width = 800;
        Config().height = 450;

#if SONDE_SANS_PLAFOND
        Config().imagesParSeconde = 0;
#else
        Config().imagesParSeconde = 60;
#endif
    }

protected:
    bool OnInit() override {
        mPassages = 0;
        mMesureEnregistree = false;
        return true;
    }

    void OnRender(nkentseu::renderer::NkRenderWindow& target) override {
        (void)target;

        ++mPassages;

#if !SONDE_SANS_LIGNE
        logger.Info("Passage {0} ; Time={1}", mPassages, Time());
#endif

        if (!mMesureEnregistree && Time() >= 10.0f) {
            mMesureEnregistree = true;

            std::ofstream fichier("sonde_mesures.txt", std::ios::app);

            if (fichier) {
                fichier
                    << "Cadence : "
#if SONDE_SANS_PLAFOND
                    << "sans plafond"
#else
                    << "plafond 60"
#endif
                    << " ; journalisation : "
#if SONDE_SANS_LIGNE
                    << "désactivée"
#else
                    << "activée"
#endif
                    << " ; passages : " << mPassages
                    << " ; Time : " << Time() << " s\n";
            }

            Quit();
        }
    }

private:
    std::uint64_t mPassages = 0;
    bool mMesureEnregistree = false;
};

} // namespace

int nkmain(const nkentseu::NkEntryState& state) {
    return nkentseu::renderer::NkCanvasApp::Run<Sonde>(state);
}
