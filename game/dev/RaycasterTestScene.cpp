#include "game/dev/RaycasterTestScene.h"

#include "imgui.h"
#include "utils/logging.h"
#include "game/controller/keyboard_player.h"

namespace game {
    RaycasterTestScene::RaycasterTestScene():
        map(TestMap()),
        player(entity::Player{{1.5, 1.5}, {1, 0}, 0.2})
    {
        raycaster = std::make_unique<engine::raycasting::Renderer>(map, player);
        logging::info("raycaster test scene loaded");
    }

    RaycasterTestScene::~RaycasterTestScene() = default;

    void RaycasterTestScene::update(float &delta_time) {
        controller::keyboard_player(player, delta_time);
        Scene::update(delta_time);
    }

    void RaycasterTestScene::render_minimap() const {
        ImGui::SetNextWindowSize(ImVec2(300, 319), ImGuiCond_Once);
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
                        case engine::WHITE:
                            color = IM_COL32_WHITE;
                            break;
                        case engine::PURPLE:
                            color = IM_COL32(218, 112, 214, 255);
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

        draw->AddEllipseFilled(
            ImVec2(
                canvas_pos.x + player.pos.x * tile_width,
                canvas_pos.y + player.pos.y * tile_height
            ),
            ImVec2(
                player.radius * tile_width,
                player.radius * tile_height
            ),
            IM_COL32(218, 112, 214, 255)
        );

        draw->AddLine(
            ImVec2(
                canvas_pos.x + player.pos.x * tile_width,
                canvas_pos.y + player.pos.y * tile_height
            ),
            ImVec2(
                canvas_pos.x + player.pos.x * tile_width + player.dir.x * 20,
                canvas_pos.y + player.pos.y * tile_height + player.dir.y * 20
            ),
            IM_COL32(218, 112, 214, 255)
        );

        ImGui::End();
    }

    void RaycasterTestScene::ui() {
        this->render_minimap();

        Scene::ui();
    }

    void RaycasterTestScene::render(engine::Window &window) const {
        raycaster->render(window);
        Scene::render(window);
    }
}
