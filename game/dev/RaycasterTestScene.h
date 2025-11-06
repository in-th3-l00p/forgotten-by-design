#ifndef RAYCASTERTESTSCENE_H
#define RAYCASTERTESTSCENE_H
#include <memory>

#include "game/dev/TestMap.h"
#include "engine/scene/Scene.h"
#include "engine/raycasting/Renderer.h"

namespace game {
    class RaycasterTestScene: public engine::Scene {
        TestMap map;
        entity::Player player;
        std::unique_ptr<engine::raycasting::Renderer> raycaster;

        void render_minimap() const;

    public:
        RaycasterTestScene();
        ~RaycasterTestScene() override;

        void update(float &delta_time) override;
        void ui() override;
        void render(engine::Window& window) const override;
    };
}

#endif //RAYCASTERTESTSCENE_H
