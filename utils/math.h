#ifndef MATH_H
#define MATH_H

#include <cmath>

namespace math {
    inline float deg2rad(float deg) { return deg * M_PI / 180.0f; }
    inline float rad2deg(float rad) { return rad * 180.0f / M_PI; }

    struct vec2 {
        float x, y;

        void rotate(float angle) {
            const float c = std::cos(angle);
            const float s = std::sin(angle);
            const float nx = c * x - s * y;
            const float ny = s * x + c * y;
            x = nx;
            y = ny;
        }

        vec2 operator+(const vec2 &other) const {
            return {x + other.x, y + other.y};
        }

        vec2 operator-(const vec2 &other) const {
            return {x - other.x, y - other.y};
        }

        vec2 operator*(float scalar) const {
            return {x * scalar, y * scalar};
        }

        vec2 operator/(float scalar) const {
            return {x / scalar, y / scalar};
        }

        vec2 &operator+=(const vec2 &other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        vec2 &operator-=(const vec2 &other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        vec2 &operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        vec2 &operator/=(float scalar) {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        [[nodiscard]] float dot(const vec2 &other) const {
            return x * other.x + y * other.y;
        }

        [[nodiscard]] float length() const {
            return std::hypot(x, y);
        }

        [[nodiscard]] vec2 normalized() const {
            const float len = length();
            if (len == 0.0f) return {0.0f, 0.0f};
            return {x / len, y / len};
        }

        friend vec2 operator*(float scalar, const vec2 &v) {
            return {v.x * scalar, v.y * scalar};
        }
    };
}

#endif //MATH_H
