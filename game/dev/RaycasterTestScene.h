#ifndef RAYCASTERTESTSCENE_H
#define RAYCASTERTESTSCENE_H
#include <memory>

#include "TestMap.h"
#include "../../engine/domain/Scene.h"
#include "../../engine/raycasting/Renderer.h"

namespace game {
    class RaycasterTestScene: public engine::Scene {
        TestMap map;
        engine::domain::Player player;
        std::unique_ptr<engine::raycasting::Renderer> raycaster;

        void render_minimap() const;

    public:
        RaycasterTestScene();
        ~RaycasterTestScene() override;

        void update(float &deltaTime) override;
        void ui() override;
        void render(engine::Window& window) const override;
    };
}

#endif //RAYCASTERTESTSCENE_H
