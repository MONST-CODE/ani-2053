#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKLogger/NkLog.h"

// NKCanvas
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Core/NkRenderer2D.h"

#include "NKMath/NKMath.h"
#include "NKMath/NkColor.h"
#include "NKTime/NkTime.h"

NKENTSEU_DEFINE_APP_DATA(([]() {
    nkentseu::NkAppData d{} ;
    d.appName = "Tetris" ;
    d.appVersion = "1.0.0";
    return d ;
})()) ;

int nkmain(const nkentseu::NkEntryState &state) {
    nkentseu::NkWindowConfig config{} ;
    config.title = state.appName ;
    config.width = 800;
    config.height = 600;

    nkentseu::NkWindow window;

    if (!window.Create(config)) {
        logger.Error("Failed to create window") ;
        return 1;
    }

    // cible
    nkentseu::NkContextDesc contextDesc;
    contextDesc.api = nkentseu::NkGraphicsApi::NK_GFX_API_OPENGL;

    nkentseu::renderer::NkRenderWindow renderWindow(window, contextDesc);

    if (!renderWindow.IsValid()) {
        logger.Error("Failed to initialize render window") ;
        return 2;
    }

    bool running = true;
    auto &eventSystem = nkentseu::NkEvents();

    nkentseu::NkClock clock;
    nkentseu::NkChrono chrono;
    nkentseu::float32 t = 0.f;

    nkentseu::math::NkRect2f tete{100, 100, 50, 50};
    nkentseu::float32 speed = 50;

    nkentseu::float32 xspeed = 0;
    nkentseu::float32 yspeed = 0;

    while (running) {
        nkentseu::float32 dt = clock.Tick().delta;

        if (dt > 0.1f)
            dt = 1.0f / 60.0f;
        t += dt;
        // t += (nkentseu::float32)chrono.Elapsed().milliseconds * 0.001f;

        nkentseu::NkEvent *event;
        while (eventSystem.PollEvent(event)) {
            if (event->Is<nkentseu::NkWindowCloseEvent>()) {
                running = false;
            }

            if (auto* keyEvent = event->As<nkentseu::NkKeyPressEvent>()) {
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_UP) {
                    yspeed = -speed * dt;
                }
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_DOWN) {
                    yspeed = speed * dt;
                }
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_LEFT) {
                    xspeed = -speed * dt;
                }
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_RIGHT) {
                    xspeed = speed * dt;
                }
            }

            if (auto* keyEvent = event->As<nkentseu::NkKeyReleaseEvent>()) {
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
        }

        tete.x += xspeed;
        tete.y += yspeed;

        renderWindow.Clear(nkentseu::renderer::NkColor2D(50, 50, 50, 255));
        nkentseu::renderer::NkRenderer2D &r2d = renderWindow.GetRenderer2D();

        r2d.DrawFilledRect(tete, nkentseu::renderer::NkColor2D{52, 84, 150, 255});

        // Rendering and game logic would go here
        renderWindow.Display();
    }

    return 0;
}
