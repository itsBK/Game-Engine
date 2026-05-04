#pragma once

#include <optional>
#include <vector>
#include <math/Vec3.hpp>

#include "Collider3.hpp"

namespace GameEngine::Physics {
using namespace GameEngine::Math;

class Ray3
{

public:
    Vec3 origin;
    Vec3 dir;

    Ray3() = default;
    Ray3(const Ray3& other) = default;
    Ray3& operator=(const Ray3& other) = default;
    ~Ray3() = default;

    Ray3(const Vec3& origin, const Vec3& direction);

    /// @return first collision, if any exists
    std::optional<Vec3> cast() const;
    /// @return a list of all colliders that the ray collided with, if any exists
    std::optional<std::vector<Bounds::Collider3>> castAll() const;
    /// @return collision point, if any exists
    std::optional<Vec3> collideWith(const Bounds::Collider3& other) const;
};

}
