#include "Renderer.h"
// Local includes for this TU
#include <SDL3/SDL.h>
#include <cmath>
#include <numbers>

// Internal helpers local to this translation unit to keep the public header clean
namespace {
    using engine::domain::Map;
    using engine::domain::Player;
    using engine::domain::Tile;
    using engine::domain::Color;
    using math::vec2;

    struct RayState {
        vec2 rayDir;
        int mapX;
        int mapY;
        float sideDistX;
        float sideDistY;
        float deltaDistX;
        float deltaDistY;
        int stepX;
        int stepY;
        int side; // 0: hit on X side, 1: hit on Y side
        bool hit;
    };

    inline vec2 perpendicular(const vec2 &v) {
        return {-v.y, v.x};
    }

    inline vec2 buildCameraPlane(const Player &player, float fovDegrees) {
        const float fovRadians = fovDegrees * std::numbers::pi_v<float> / 180.0f;
        const float planeScale = std::tan(fovRadians / 2.0f);
        return perpendicular(player.dir).normalized() * planeScale;
    }

    inline float safeInv(float x) {
        constexpr float big = 1e30f;
        if (x == 0.0f) return big;
        return 1.0f / x;
    }

    inline RayState initRayForColumn(int x, int width, const Player &player, const vec2 &cameraPlane) {
        const float cameraX = 2.0f * static_cast<float>(x) / static_cast<float>(width) - 1.0f;
        const vec2 rayDir = player.dir + cameraPlane * cameraX;

        RayState rs{};
        rs.rayDir = rayDir;
        rs.mapX = static_cast<int>(player.pos.x);
        rs.mapY = static_cast<int>(player.pos.y);

        // Precompute distances between successive x and y grid lines
        rs.deltaDistX = std::abs(safeInv(rayDir.x));
        rs.deltaDistY = std::abs(safeInv(rayDir.y));

        // Establish initial step and first side distance
        if (rayDir.x < 0.0f) {
            rs.stepX = -1;
            rs.sideDistX = (player.pos.x - static_cast<float>(rs.mapX)) * rs.deltaDistX;
        } else {
            rs.stepX = 1;
            rs.sideDistX = (static_cast<float>(rs.mapX + 1) - player.pos.x) * rs.deltaDistX;
        }

        if (rayDir.y < 0.0f) {
            rs.stepY = -1;
            rs.sideDistY = (player.pos.y - static_cast<float>(rs.mapY)) * rs.deltaDistY;
        } else {
            rs.stepY = 1;
            rs.sideDistY = (static_cast<float>(rs.mapY + 1) - player.pos.y) * rs.deltaDistY;
        }

        rs.side = 0;
        rs.hit = false;
        return rs;
    }

    inline bool isInsideMap(const Map &map, int mx, int my) {
        return mx >= 0 && my >= 0 && mx < static_cast<int>(map.get_width()) && my < static_cast<int>(map.get_height());
    }

    inline bool isWall(const Map &map, int mx, int my) {
        const Tile t = map.get_tile(static_cast<std::uint32_t>(mx), static_cast<std::uint32_t>(my));
        return t.color.has_value();
    }

    inline void performDDA(const Map &map, RayState &rs) {
        // Hard cap to prevent infinite loops on malformed maps/directions
        constexpr int maxSteps = 1 << 16;
        int steps = 0;
        while (!rs.hit && steps++ < maxSteps) {
            if (rs.sideDistX < rs.sideDistY) {
                rs.sideDistX += rs.deltaDistX;
                rs.mapX += rs.stepX;
                rs.side = 0;
            } else {
                rs.sideDistY += rs.deltaDistY;
                rs.mapY += rs.stepY;
                rs.side = 1;
            }

            if (!isInsideMap(map, rs.mapX, rs.mapY)) {
                // out of bounds: stop the ray; no hit recorded
                break;
            }
            if (isWall(map, rs.mapX, rs.mapY)) {
                rs.hit = true;
                break;
            }
        }
    }

    inline float perpendicularWallDistance(const Player &player, const RayState &rs) {
        // Avoid division by zero for degenerate rays
        constexpr float epsilon = 1e-6f;
        if (rs.side == 0) {
            const float denom = (std::abs(rs.rayDir.x) < epsilon) ? (rs.rayDir.x < 0 ? -epsilon : epsilon) : rs.rayDir.x;
            return (static_cast<float>(rs.mapX) - player.pos.x + (1.0f - static_cast<float>(rs.stepX)) * 0.5f) / denom;
        } else {
            const float denom = (std::abs(rs.rayDir.y) < epsilon) ? (rs.rayDir.y < 0 ? -epsilon : epsilon) : rs.rayDir.y;
            return (static_cast<float>(rs.mapY) - player.pos.y + (1.0f - static_cast<float>(rs.stepY)) * 0.5f) / denom;
        }
    }

    inline SDL_Color colorForTile(const Map &map, int mx, int my, int side) {
        SDL_Color color{255, 255, 255, 255};
        const Tile t = map.get_tile(static_cast<std::uint32_t>(mx), static_cast<std::uint32_t>(my));
        if (t.color.has_value()) {
            switch (t.color.value()) {
                case Color::WHITE: color = SDL_Color{255, 255, 255, 255}; break;
                case Color::PURPLE: color = SDL_Color{218, 112, 214, 255}; break;
                default: break;
            }
        }
        if (side == 1) { // simple shading for y-sides
            color.r = static_cast<Uint8>(color.r * 0.6f);
            color.g = static_cast<Uint8>(color.g * 0.6f);
            color.b = static_cast<Uint8>(color.b * 0.6f);
        }
        return color;
    }

    inline void drawVerticalLine(SDL_Renderer *renderer, int x, int start, int end, const SDL_Color &color) {
        if (start > end) return;
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderLine(renderer,
                       static_cast<float>(x), static_cast<float>(start),
                       static_cast<float>(x), static_cast<float>(end));
    }
}

namespace engine::raycasting {
    void Renderer::render(Window &window) const {
        int screenW = 0, screenH = 0;
        SDL_GetRenderOutputSize(window.renderer1(), &screenW, &screenH);
        if (screenW <= 0 || screenH <= 0) return;

        // Build camera plane from player orientation; 66° mimics classic raycasters (plane length ~0.66)
        const math::vec2 cameraPlane = buildCameraPlane(player, 66.0f);

        for (int x = 0; x < screenW; ++x) {
            RayState ray = initRayForColumn(x, screenW, player, cameraPlane);
            performDDA(map, ray);
            if (!ray.hit) continue;

            const float perpDist = perpendicularWallDistance(player, ray);
            if (perpDist <= 0.0f) continue;

            const int lineHeight = static_cast<int>(static_cast<float>(screenH) / perpDist);
            int drawStart = -lineHeight / 2 + screenH / 2;
            int drawEnd = lineHeight / 2 + screenH / 2;
            if (drawStart < 0) drawStart = 0;
            if (drawEnd >= screenH) drawEnd = screenH - 1;

            const SDL_Color color = colorForTile(map, ray.mapX, ray.mapY, ray.side);
            drawVerticalLine(window.renderer1(), x, drawStart, drawEnd, color);
        }
    }
} // raycasting
