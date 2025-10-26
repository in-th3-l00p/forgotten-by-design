//
// Created by Tisca Catalin on 26.10.2025.
//

#include "RaycasterTestScene.h"

namespace game {
    RaycasterTestScene::RaycasterTestScene():
        map(TestMap()),
        player(engine::domain::Player { 1.5, 1.5, 0.2 })
    {
        raycaster = std::make_unique<engine::raycasting::Renderer>(map, player);
    }

    RaycasterTestScene::~RaycasterTestScene() = default;

    void RaycasterTestScene::update(const float deltaTime) {
        Scene::update(deltaTime);
    }

    void RaycasterTestScene::render(engine::Window &window) const {
        Scene::render(window);
    }
}
