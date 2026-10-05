#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKLogger/NkLog.h"

// NKCanvas
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Core/NkRenderer2D.h"
#include "NKCanvas/App/NkCanvasApp.h"

#include "NKMath/NKMath.h"
#include "NKMath/NkColor.h"
#include "NKTime/NkTime.h"

NKENTSEU_DEFINE_APP_DATA(([]() {
    nkentseu::NkAppData d{} ;
    d.appName = "Tetris" ;
    d.appVersion = "1.0.0";
    return d ;
})()) ;

class Tetris : public nkentseu::renderer::NkCanvasApp {
    private:
        nkentseu::math::NkRect2f tete{100, 100, 50, 50};
        nkentseu::float32 speed = 50;

        nkentseu::float32 xspeed = 0;
        nkentseu::float32 yspeed = 0;

        nkentseu::float32 t = 0.f;
        nkentseu::float32 deltaTime = 0.f;
    public:
        Tetris() {
            Config().title = "Tetris";
        }

        bool OnInit() override {

            return true;
        }

        void OnUpdate(nkentseu::float32 deltaTime) override {
            this->deltaTime = deltaTime;
            // Logique de mise à jour du jeu
            if (this->deltaTime)
                this->deltaTime = 1.0f / 60.0f;
            t += this->deltaTime;
        }

        void OnRender(nkentseu::renderer::NkRenderWindow &target) override {
            tete.x += xspeed;
            tete.y += yspeed;

            nkentseu::renderer::NkRenderer2D &r2d = target.GetRenderer2D();
            r2d.DrawFilledRect(tete, nkentseu::renderer::NkColor2D{52, 84, 150, 255});
        }

        bool OnEvent(const nkentseu::NkEvent &event) override {
            if (auto* keyEvent = event.As<nkentseu::NkKeyPressEvent>()) {
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_UP) {
                    yspeed = -speed * deltaTime;
                }
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_DOWN) {
                    yspeed = speed * deltaTime;
                }
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_LEFT) {
                    xspeed = -speed * deltaTime;
                }
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_RIGHT) {
                    xspeed = speed * deltaTime;
                }
            }

            if (auto* keyEvent = event.As<nkentseu::NkKeyReleaseEvent>()) {
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_UP) {
                    yspeed = 0;
                }
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_DOWN) {
                    yspeed = 0;
                }
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_LEFT) {
                    xspeed = 0;
                }
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_RIGHT) {
                    xspeed = 0;
                }
            }
            return false;
        }
};

int nkmain(const nkentseu::NkEntryState &state) {
    return nkentseu::renderer::NkCanvasApp::Run<Tetris>(state) ;
}
