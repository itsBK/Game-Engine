#pragma once

#include <optional>
#include <vector>
#include <math/Vec2.hpp>

namespace GameEngine::Physics {
using namespace GameEngine::Math;

class Collider2
{

public:
    virtual ~Collider2() = default;

    virtual bool contains(const Vec2& point) const = 0;
    virtual bool collides(const Collider2& other) const = 0;
    /// @return collision point, if it exists
    virtual std::optional<Vec2> collideWith(const Collider2& other) const = 0;
    /// @return a list of all colliders that this collider collided with, if any exists
    virtual std::optional<std::vector<Collider2>> allCollisions() const = 0;
};

}
