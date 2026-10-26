
#include "NKWindow/Core/NkEntry.h"
#include "NKWindow/NKMain.h"

#include "NKCanvas/App/NkCanvasApp.h"
#include "NKCanvas/Renderer/Core/NkDrawable.h"
#include "NKCanvas/Renderer/Targets/NkRenderTarget.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

// Métadonnées de l'application, conformément au chapitre 15.
NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData data{};
    data.appName = "Exercice 5 - Qui appelle vraiment";
    data.appVersion = "1.0.0";
    return data;
})());

// Objet concret qui redéfinit la méthode virtuelle Draw de NkDrawable.
class AppelantTest final : public NkDrawable
{
public:
    void Draw(
        NkRenderTarget& target,
        const NkRenderStates& states
    ) const override
    {
        const NkVertex vertices[4] =
        {
            // Premier segment : horizontal.
            { 200.0f, 200.0f, 0.0f, 0.0f, 255, 0,   0,   255 },
            { 400.0f, 200.0f, 0.0f, 0.0f, 255, 0,   0,   255 },

            // Deuxième segment : vertical.
            { 300.0f, 100.0f, 0.0f, 0.0f, 0,   255, 0,   255 },
            { 300.0f, 300.0f, 0.0f, 0.0f, 0,   255, 0,   255 }
        };

        target.Draw(
            vertices,
            4,
            NkPrimitiveType::NK_LINES,
            states
        );
    }
};

// Coquille d'application Nkentseu.
class AppelantsApp final : public NkCanvasApp
{
public:
    AppelantsApp() = default;

protected:
    void OnRender(NkRenderWindow& target) override
    {
        target.Draw(mObjet);
    }

private:
    AppelantTest mObjet;
};

// Point d'entrée portable de Nkentseu.
int nkmain(const NkEntryState& state)
{
    return NkCanvasApp::Run<AppelantsApp>(state);
}
