#include "RaycasterTestScene.h"

#include "imgui.h"
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

    void RaycasterTestScene::ui() {
        ImGui::SetNextWindowSize(ImVec2(200, 215), ImGuiCond_Once);
        ImGui::Begin("Minimap", nullptr, ImGuiWindowFlags_NoResize);

        auto canvas_pos = ImGui::GetCursorScreenPos();
        auto canvas_size = ImGui::GetContentRegionAvail();
        auto draw = ImGui::GetWindowDrawList();
        auto tile_width = canvas_size.x / static_cast<float>(map.get_width());
        auto tile_height = canvas_size.y / static_cast<float>(map.get_height());
        for (int x = 0; x < map.get_width(); x++)
            for (int y = 0; y < map.get_height(); y++) {
                ImU32 color = IM_COL32_BLACK;
                if (map.get_tile(x, y).color.has_value()) {
                    switch (map.get_tile(x, y).color.value()) {
                        case engine::domain::WHITE:
                            color = IM_COL32_WHITE;
                            break;
                        case engine::domain::PURPLE:
                            color = IM_COL32(218,112,214, 255);
                            break;
                        default:
                            break;
                    }
                }

                draw->AddRectFilled(
                    ImVec2(
                        canvas_pos.x + static_cast<float>(x) * tile_width,
                        canvas_pos.y + static_cast<float>(y) * tile_height
                        ),
                    ImVec2(
                        canvas_pos.x + static_cast<float>(x + 1) * tile_width,
                        canvas_pos.y + static_cast<float>(y + 1) * tile_height
                        ),
                    color
                );
            }
        ImGui::End();

        Scene::ui();
    }

    void RaycasterTestScene::render(engine::Window &window) const {
        raycaster->render(window);
        Scene::render(window);
    }
}
