#pragma once

#include <optional>
#include <vector>
#include <math/Vec3.hpp>

namespace GameEngine::Physics {
using namespace GameEngine::Math;

class Collider3
{

public:
    virtual ~Collider3() = default;

    virtual bool contains(const Vec3& point) const = 0;
    virtual bool collides(const Collider3& other) const = 0;
    /// @return collision point, if it exists
    virtual std::optional<Vec3> collideWith(const Collider3& other) const = 0;
    /// @return a list of all colliders that this collider collided with, if any exists
    virtual std::optional<std::vector<Collider3>> allCollisions() const = 0;
};

}
