#include "include/physics/3d-colliders/AABB.hpp"

using namespace GameEngine::Physics::Bounds;


AABB::AABB(const Vec3& pos, const Vec3& size)
    : pos(pos), size(size) {}

AABB::AABB(const Vec3& min, const Vec3& max, bool /*isMinMax*/)
    : pos((min + max) * 0.5), size(max - min) {}

bool AABB::operator!=(const AABB& other) const
{
    return pos != other.pos || size != other.size;
}

bool AABB::operator==(const AABB& other) const
{
    return pos == other.pos && size == other.size;
}

inline Vec3 AABB::min() const
{
    return pos - size * 0.5;
}

inline Vec3 AABB::max() const
{
    return pos + size * 0.5;
}

bool AABB::contains(const Vec3& point) const
{
    Vec3 m = min();
    Vec3 mx = max();
    return point.x >= m.x && point.x <= mx.x &&
           point.y >= m.y && point.y <= mx.y &&
           point.z >= m.z && point.z <= mx.z;
}

bool AABB::contains(const AABB& other) const
{
    return contains(other.min()) && contains(other.max());
}
