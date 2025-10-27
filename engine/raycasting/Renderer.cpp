#include "Renderer.h"
#include <SDL3/SDL.h>
#include <cmath>
#include <numbers>

namespace {
    using math::vec2;
    using engine::Player;
    using engine::Map;
    using engine::Tile;
    using engine::Color;

    struct RayState {
        vec2 ray_dir;
        int map_x, map_y;
        float side_dist_x;
        float side_dist_y;
        float delta_dist_x;
        float delta_dist_y;
        int step_x;
        int step_y;
        int side; // 0: hit on X side, 1: hit on Y side
        bool hit;
    };

    vec2 perpendicular(const vec2 &v) {
        return {-v.y, v.x};
    }

    vec2 build_camera_plane(const Player &player, float fov_degrees) {
        const float fovRadians = fov_degrees * std::numbers::pi_v<float> / 180.0f;
        const float planeScale = std::tan(fovRadians / 2.0f);
        return perpendicular(player.dir).normalized() * planeScale;
    }

    float safe_inv(float x) {
        constexpr float big = 1e30f;
        if (x == 0.0f)
            return big;
        return 1.0f / x;
    }

    RayState init_ray_for_column(
        int x,
        int width,
        const Player &player,
        const vec2 &camera_plane
    ) {
        const float camera_x = 2.0f * static_cast<float>(x) / static_cast<float>(width) - 1.0f;
        const vec2 ray_dir = player.dir + camera_plane * camera_x;

        RayState rs{};
        rs.ray_dir = ray_dir;
        rs.map_x = static_cast<int>(player.pos.x);
        rs.map_y = static_cast<int>(player.pos.y);

        // precompute distances between successive x and y grid lines
        rs.delta_dist_x = std::abs(safe_inv(ray_dir.x));
        rs.delta_dist_y = std::abs(safe_inv(ray_dir.y));

        // establish initial step and first side distance
        if (ray_dir.x < 0.0f) {
            rs.step_x = -1;
            rs.side_dist_x = (player.pos.x - static_cast<float>(rs.map_x)) * rs.delta_dist_x;
        } else {
            rs.step_x = 1;
            rs.side_dist_x = (static_cast<float>(rs.map_x + 1) - player.pos.x) * rs.delta_dist_x;
        }

        if (ray_dir.y < 0.0f) {
            rs.step_y = -1;
            rs.side_dist_y = (player.pos.y - static_cast<float>(rs.map_y)) * rs.delta_dist_y;
        } else {
            rs.step_y = 1;
            rs.side_dist_y = (static_cast<float>(rs.map_y + 1) - player.pos.y) * rs.delta_dist_y;
        }

        rs.side = 0;
        rs.hit = false;
        return rs;
    }

    bool is_inside_map(const Map &map, int map_x, int map_y) {
        return map_x >= 0 && map_y >= 0 &&
               map_x < static_cast<int>(map.get_width()) &&
               map_y < static_cast<int>(map.get_height());
    }

    bool is_wall(const Map &map, int map_x, int map_y) {
        const Tile t = map.get_tile(
            static_cast<std::uint32_t>(map_x),
            static_cast<std::uint32_t>(map_y)
        );
        return t.color.has_value();
    }

    void perform_dda(const Map &map, RayState &state) {
        // hard cap to prevent infinite loops on malformed maps/directions
        constexpr int max_steps = 1 << 16;
        int steps = 0;
        while (!state.hit && steps++ < max_steps) {
            if (state.side_dist_x < state.side_dist_y) {
                state.side_dist_x += state.delta_dist_x;
                state.map_x += state.step_x;
                state.side = 0;
            } else {
                state.side_dist_y += state.delta_dist_y;
                state.map_y += state.step_y;
                state.side = 1;
            }

            if (!is_inside_map(map, state.map_x, state.map_y)) {
                // out of bounds: stop the ray; no hit recorded
                break;
            }
            if (is_wall(map, state.map_x, state.map_y)) {
                state.hit = true;
                break;
            }
        }
    }

    float calculate_perpendicular_wall_distance(
        const Player &player,
        const RayState &state
    ) {
        // avoid division by zero for degenerate rays
        constexpr float epsilon = 1e-6f;
        if (state.side == 0) {
            // horizontal
            const float denom = (std::abs(state.ray_dir.x) < epsilon)
                                    ? (state.ray_dir.x < 0 ? -epsilon : epsilon)
                                    : state.ray_dir.x;
            return (static_cast<float>(state.map_x) - player.pos.x + (1.0f - static_cast<float>(state.step_x)) * 0.5f) /
                   denom;
        }

        const float denom = (std::abs(state.ray_dir.y) < epsilon)
                                ? (state.ray_dir.y < 0 ? -epsilon : epsilon)
                                : state.ray_dir.y;
        return (static_cast<float>(state.map_y) - player.pos.y + (1.0f - static_cast<float>(state.step_y)) * 0.5f) /
               denom;
    }

    SDL_Color get_color_for_tile(const Map &map, int map_x, int map_y, int side) {
        SDL_Color color{255, 255, 255, 255};
        const Tile t = map.get_tile(static_cast<std::uint32_t>(map_x), static_cast<std::uint32_t>(map_y));
        if (t.color.has_value()) {
            switch (t.color.value()) {
                case Color::WHITE: color = SDL_Color{255, 255, 255, 255};
                    break;
                case Color::PURPLE: color = SDL_Color{218, 112, 214, 255};
                    break;
                default: break;
            }
        }
        if (side == 1) {
            // simple shading for y-sides
            color.r = static_cast<Uint8>(color.r * 0.6f);
            color.g = static_cast<Uint8>(color.g * 0.6f);
            color.b = static_cast<Uint8>(color.b * 0.6f);
        }
        return color;
    }

    void draw_vertical_line(SDL_Renderer *renderer, int x, int start, int end, const SDL_Color &color) {
        if (start > end)
            return;
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderLine(renderer,
                       static_cast<float>(x), static_cast<float>(start),
                       static_cast<float>(x), static_cast<float>(end));
    }
}

namespace engine::raycasting {
    void Renderer::render(Window &window) const {
        int screen_width = 0, screen_height = 0;
        SDL_GetRenderOutputSize(window.get_renderer(), &screen_width, &screen_height);
        if (screen_width <= 0 || screen_height <= 0)
            return;

        // build camera plane from player orientation; 66° mimics classic raycasters (plane length ~0.66)
        const vec2 cameraPlane = build_camera_plane(player, 66.0f);

        for (int x = 0; x < screen_width; ++x) {
            RayState ray = init_ray_for_column(x, screen_width, player, cameraPlane);
            perform_dda(map, ray);
            if (!ray.hit)
                continue;

            const float perpDist = calculate_perpendicular_wall_distance(player, ray);
            if (perpDist <= 0.0f)
                continue;

            const int lineHeight = static_cast<int>(static_cast<float>(screen_height) / perpDist);
            int drawStart = -lineHeight / 2 + screen_height / 2;
            int drawEnd = lineHeight / 2 + screen_height / 2;
            if (drawStart < 0)
                drawStart = 0;
            if (drawEnd >= screen_height)
                drawEnd = screen_height - 1;

            const SDL_Color color = get_color_for_tile(map, ray.map_x, ray.map_y, ray.side);
            draw_vertical_line(window.get_renderer(), x, drawStart, drawEnd, color);
        }
    }
} // raycasting
