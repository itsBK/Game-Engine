#pragma once

#include <math/Vec3.hpp>

#include <math/Transform3.hpp>

namespace GameEngine::Physics::Bounds {
using namespace GameEngine::Math;

class AABB
{
    Vec3 m_min;
    Vec3 m_max;

public:
    Vec3 center = {};
    Vec3 size = {1,1,1};

    AABB() = default;
    AABB(const AABB& other) = default;
    AABB& operator=(const AABB& other) = default;
    ~AABB() = default;

    AABB(const Vec3& pos, const Vec3& size);
    AABB(const Vec3& min, const Vec3& max, bool MinMax);

    bool operator!=(const AABB& other) const;
    bool operator==(const AABB& other) const;

    void update(const Transform3& transform, const Vec3& offset = {});

    const Vec3& min() const;
    const Vec3& max() const;

    bool contains(const Vec3& point) const;
    bool contains(const AABB& other) const;
};

}
