#pragma once

#include <math/Vec3.hpp>

namespace GameEngine::Physics::Bounds {
using namespace GameEngine::Math;

class AABB
{
public:
    Vec3 pos = {};
    Vec3 size = {1,1,1};

    AABB() = default;
    AABB(const AABB& other) = default;
    AABB& operator=(const AABB& other) = default;
    ~AABB() = default;

    AABB(const Vec3& pos, const Vec3& size);
    AABB(const Vec3& min, const Vec3& max, bool isMinMax);

    bool operator!=(const AABB& other) const;
    bool operator==(const AABB& other) const;

    inline Vec3 min() const;
    inline Vec3 max() const;

    bool contains(const Vec3& point) const;
    bool contains(const AABB& other) const;
};

}
