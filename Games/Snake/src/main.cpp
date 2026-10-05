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

#include <vector>
#include <cmath>

NKENTSEU_DEFINE_APP_DATA(([]() {
    nkentseu::NkAppData d{};
    d.appName = "Physic2D Simulation";
    d.appVersion = "1.0.0";
    return d;
})()) ;

// --- STRUCTURES PHYSIQUES ---

struct Particle {
    nkentseu::math::NkVector2f position;
    nkentseu::math::NkVector2f oldPosition;
    nkentseu::math::NkVector2f acceleration;
    nkentseu::float32 radius;
    nkentseu::renderer::NkColor2D color;
    bool isStatic;
};

struct Constraint {
    size_t particleA;
    size_t particleB;
    nkentseu::float32 restLength;
    nkentseu::float32 stiffness; // Élasticité (1.0 = rigide, <1.0 = mou/ressort)
    bool isCloth; // Pour différencier le rendu si nécessaire
};

// --- SIMULATION ---

class Physic2D : public nkentseu::renderer::NkCanvasApp {
    private:
        std::vector<Particle> m_particles;
        std::vector<Constraint> m_constraints;
        
        nkentseu::math::NkVector2f m_gravity = { 0.0f, 500.0f }; // Gravité vers le bas
        nkentseu::float32 m_boundsWidth = 1280.0f;
        nkentseu::float32 m_boundsHeight = 720.0f;
        int m_subSteps = 8; // Sous-étapes pour stabiliser la physique (Verlet)

    public:
        Physic2D() {
            Config().title = "Physic2D - Soft Bodies, Particles & Cloth";
            Config().width = static_cast<nkentseu::uint32>(m_boundsWidth);
            Config().height = static_cast<nkentseu::uint32>(m_boundsHeight);
        }

        bool OnInit() override {
            // 1. Génération d'un Ballon / Blob (Corps mou circulaire)
            CreateSoftBodyCircle({ 300.0f, 200.0f }, 80.0f, 16, 0.5f);

            // 2. Génération d'un Tissu Élastique suspendu (Cloth)
            CreateCloth({ 600.0f, 50.0f }, 10, 10, 20.0f, 0.9f);

            // 3. Génération de particules libres (Sable / Liquide)
            for (int i = 0; i < 50; ++i) {
                Particle p;
                p.position = { 100.0f + (i * 8.0f), 100.0f + (i * 2.0f) };
                p.oldPosition = p.position;
                p.acceleration = { 0.0f, 0.0f };
                p.radius = 6.0f;
                p.color = nkentseu::renderer::NkColor2D::Yellow;
                p.isStatic = false;
                m_particles.push_back(p);
            }

            return true;
        }

        void CreateSoftBodyCircle(nkentseu::math::NkVector2f center, nkentseu::float32 radius, int points, nkentseu::float32 stiffness) {
            size_t startIdx = m_particles.size();

            // Création du noyau central
            Particle centerP{ center, center, {0,0}, 10.0f, nkentseu::renderer::NkColor2D::Red, false };
            m_particles.push_back(centerP);

            // Création du contour moléculaire (atomes)
            for (int i = 0; i < points; ++i) {
                nkentseu::float32 angle = (static_cast<nkentseu::float32>(i) / points) * 2.0f * 3.14159265f;
                nkentseu::math::NkVector2f pos = center + nkentseu::math::NkVector2f(std::cos(angle), std::sin(angle)) * radius;
                
                Particle p{ pos, pos, {0,0}, 7.0f, nkentseu::renderer::NkColor2D::Cyan, false };
                m_particles.push_back(p);

                // Contrainte vers le centre (maintient la forme de ballon)
                m_constraints.push_back({ startIdx, m_particles.size() - 1, radius, stiffness, false });
            }

            // Liaisons structurelles du contour (ressorts internes interconnectés)
            for (int i = 0; i < points; ++i) {
                size_t p1 = startIdx + 1 + i;
                size_t p2 = startIdx + 1 + ((i + 1) % points);
                size_t p3 = startIdx + 1 + ((i + 2) % points); // Ressorts croisés de stabilité

                nkentseu::float32 dist1 = (m_particles[p1].position - m_particles[p2].position).Len();
                m_constraints.push_back({ p1, p2, dist1, stiffness, false });

                nkentseu::float32 dist2 = (m_particles[p1].position - m_particles[p3].position).Len();
                m_constraints.push_back({ p1, p3, dist2, stiffness, false });
            }
        }

        void CreateCloth(nkentseu::math::NkVector2f origin, int width, int height, nkentseu::float32 spacing, nkentseu::float32 stiffness) {
            size_t startIdx = m_particles.size();

            // Création du maillage d'atomes
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    nkentseu::math::NkVector2f pos = origin + nkentseu::math::NkVector2f(x * spacing, y * spacing);
                    
                    // Fixer les deux coins supérieurs pour suspendre le tissu
                    bool isStatic = (y == 0 && (x == 0 || x == width - 1 || x == width / 2));
                    nkentseu::renderer::NkColor2D col = isStatic ? nkentseu::renderer::NkColor2D::White : nkentseu::renderer::NkColor2D::Green;

                    m_particles.push_back({ pos, pos, {0,0}, 4.0f, col, isStatic });
                }
            }

            // Génération des liaisons de structure (voisins directs et diagonales)
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    size_t current = startIdx + y * width + x;

                    if (x < width - 1) { // Horizontal
                        m_constraints.push_back({ current, current + 1, spacing, stiffness, true });
                    }
                    if (y < height - 1) { // Vertical
                        m_constraints.push_back({ current, current + width, spacing, stiffness, true });
                    }
                }
            }
        }

        void OnUpdate(nkentseu::float32 deltaTime) override {
            // Éviter les sauts physiques si baisse de framerate
            if (deltaTime > 0.1f) deltaTime = 0.1f;

            nkentseu::float32 subDt = deltaTime / m_subSteps;

            for (int step = 0; step < m_subSteps; ++step) {
                // 1. Intégration de Verlet (Mouvement des atomes)
                for (auto &p : m_particles) {
                    if (p.isStatic) continue;

                    nkentseu::math::NkVector2f velocity = p.position - p.oldPosition;
                    p.oldPosition = p.position;
                    
                    // Ajout des forces (Gravité)
                    p.position = p.position + velocity + (p.acceleration + m_gravity) * (subDt * subDt);
                    p.acceleration = { 0.0f, 0.0f }; // Reset des forces
                }

                // 2. Résolution des Contraintes Élastiques (Ressorts)
                for (auto &c : m_constraints) {
                    auto &pA = m_particles[c.particleA];
                    auto &pB = m_particles[c.particleB];

                    nkentseu::math::NkVector2f delta = pB.position - pA.position;
                    nkentseu::float32 currentLen = delta.Len();
                    if (currentLen < 0.0001f) currentLen = 0.0001f;

                    nkentseu::float32 diff = c.restLength - currentLen;
                    // Loi de Hooke simplifiée intégrée directement dans Verlet
                    nkentseu::float32 percent = (diff / currentLen) * 0.5f * c.stiffness;
                    nkentseu::math::NkVector2f offset = delta * percent;

                    if (!pA.isStatic) pA.position = pA.position - offset;
                    if (!pB.isStatic) pB.position = pB.position + offset;
                }

                // 3. Collisions Particule contre Particule (Inter-atomes)
                for (size_t i = 0; i < m_particles.size(); ++i) {
                    for (size_t j = i + 1; j < m_particles.size(); ++j) {
                        auto &pA = m_particles[i];
                        auto &pB = m_particles[j];

                        nkentseu::math::NkVector2f delta = pB.position - pA.position;
                        nkentseu::float32 dist = delta.Len();
                        nkentseu::float32 minDist = pA.radius + pB.radius;

                        if (dist < minDist) {
                            if (dist < 0.001f) continue;
                            nkentseu::math::NkVector2f overlap = delta * ((minDist - dist) / dist * 0.5f);
                            
                            if (!pA.isStatic) pA.position = pA.position - overlap;
                            if (!pB.isStatic) pB.position = pB.position + overlap;
                        }
                    }
                }

                // 4. Collisions avec les bords de la fenêtre NKWindow
                for (auto &p : m_particles) {
                    if (p.isStatic) continue;

                    // Sol
                    if (p.position.y > m_boundsHeight - p.radius) {
                        p.position.y = m_boundsHeight - p.radius;
                    }
                    // Plafond
                    if (p.position.y < p.radius) {
                        p.position.y = p.radius;
                    }
                    // Mur Gauche
                    if (p.position.x < p.radius) {
                        p.position.x = p.radius;
                    }
                    // Mur Droit
                    if (p.position.x > m_boundsWidth - p.radius) {
                        p.position.x = m_boundsWidth - p.radius;
                    }
                }
            }
        }

        void OnRender(nkentseu::renderer::NkRenderWindow &target) override {
            // Effacer l'écran en noir profond
            target.Clear(nkentseu::renderer::NkColor2D::Black);

            // Obtenir le contexte de dessin 2D du framework
            auto& renderer = target.GetRenderer2D();

            // 1. Dessiner les contraintes (Liaisons / Fibres élastiques)
            for (const auto &c : m_constraints) {
                const auto &pA = m_particles[c.particleA];
                const auto &pB = m_particles[c.particleB];
                nkentseu::renderer::NkColor2D linkColor = c.isCloth ? nkentseu::renderer::NkColor2D(100, 200, 100, 255) : nkentseu::renderer::NkColor2D(100, 100, 255, 255);
                renderer.DrawLine(pA.position, pB.position, linkColor);
            }

            // 2. Dessiner les Atomes / Particules
            for (const auto &p : m_particles) {
                renderer.DrawCircle(p.position, p.radius, p.color);
            }
        }

        bool OnEvent(const nkentseu::NkEvent &event) override {
            // Interaction à la souris : Cliquer et déplacer des objets ou injecter des impulsions
            if (auto* mouseEvent = event.As<nkentseu::NkMouseButtonPressEvent>()) {
                // Exemple : Ajouter une force d'explosion au clic
                nkentseu::math::NkVector2f mousePos = { static_cast<nkentseu::float32>(mouseEvent->GetX()), static_cast<nkentseu::float32>(mouseEvent->GetY()) };
                for (auto &p : m_particles) {
                    nkentseu::math::NkVector2f dir = p.position - mousePos;
                    nkentseu::float32 dist = dir.Len();
                    if (dist < 150.0f && dist > 0.1f) {
                        nkentseu::float32 force = (150.0f - dist) * 10.0f;
                        p.position = p.position + (dir * (force / dist)); // Impulsion instantanée Verlet
                    }
                }
                return true;
            }
            return false;
        }
};

int nkmain(const nkentseu::NkEntryState &state) {
    return nkentseu::renderer::NkCanvasApp::Run<Physic2D>(state) ;
}
