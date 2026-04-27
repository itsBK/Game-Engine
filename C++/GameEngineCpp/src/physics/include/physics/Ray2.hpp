#pragma once

#include <optional>
#include <vector>
#include <math/Vec2.hpp>

namespace GameEngine::Physics {
using namespace GameEngine::Math;
class Collider2;

class Ray2
{

public:
    Vec2 origin;
    Vec2 dir;

    Ray2() = default;
    Ray2(const Ray2& other) = default;
    Ray2& operator=(const Ray2& other) = default;
    ~Ray2() = default;

    Ray2(const Vec2& origin, const Vec2& direction);

    /// @return first collision, if any exists
    std::optional<Vec2> cast() const;
    /// @return a list of all colliders that the ray collided with, if any exists
    std::optional<std::vector<Collider2>> castAll() const;
    /// @return collision point, if it exists
    std::optional<Vec2> collideWith(const Collider2& other) const;
};

}
