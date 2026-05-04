#pragma once

#include <array>

#include <math/Vec3.hpp>
#include <math/Transform3.hpp>

#include "AABB.hpp"

namespace GameEngine::Physics::Bounds {
using namespace GameEngine::Math;

class OBB
{
    AABB _aabb;
    std::array<Vec3, 8> _corners;

public:
    Transform3 transform;
    Vec3 size = {1, 1, 1};

    OBB() = default;
    OBB(const OBB& other) = default;
    OBB& operator=(const OBB& other) = default;
    ~OBB() = default;

    OBB(const Vec3& pos, const Vec3& forward, const Vec3& left, const Vec3& size);
    OBB(const Transform3& transform, const Vec3& size);

    bool operator!=(const OBB& other) const;
    bool operator==(const OBB& other) const;

    bool contains(const Vec3& point);

    //TODO: those should be updated automatically in the physics update step
    const AABB& calcAABB();
    const std::array<Vec3, 8>& corners();
};

}
