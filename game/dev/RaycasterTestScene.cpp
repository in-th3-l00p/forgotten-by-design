#include "RaycasterTestScene.h"

#include "../../utils/Logging.h"

namespace game {
    RaycasterTestScene::RaycasterTestScene():
        map(TestMap()),
        player(engine::domain::Player { 1.5, 1.5, 0.2 })
    {
        raycaster = std::make_unique<engine::raycasting::Renderer>(map, player);
        logging::info("raycaster test scene loaded");
    }

    RaycasterTestScene::~RaycasterTestScene() = default;

    void RaycasterTestScene::update(const float deltaTime) {
        Scene::update(deltaTime);
    }

    void RaycasterTestScene::render(engine::Window &window) const {
        raycaster->render(window);
        Scene::render(window);
    }
}
