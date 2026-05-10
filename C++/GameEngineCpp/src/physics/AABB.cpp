#include "include/physics/3d-colliders/AABB.hpp"

using namespace GameEngine::Physics::Bounds;


AABB::AABB(const Vec3& pos, const Vec3& size)
    : center(pos), size(size) {}

AABB::AABB(const Vec3& min, const Vec3& max, bool /*isMinMax*/)
    : center((min + max) * 0.5), size(max - min) {}

bool AABB::operator!=(const AABB& other) const
{
    return center != other.center || size != other.size;
}

bool AABB::operator==(const AABB& other) const
{
    return center == other.center && size == other.size;
}

void AABB::update(const Transform3 &transform, const Vec3 &offset)
{
    center = transform.pos;
    center += transform.local(offset);
    m_min = center - size * 0.5;
    m_max = center + size * 0.5;
}


const Vec3& AABB::min() const
{
    return m_min;
}

const Vec3& AABB::max() const
{
    return m_max;
}

bool AABB::contains(const Vec3& point) const
{
    return point.x >= m_min.x && point.x <= m_max.x &&
           point.y >= m_min.y && point.y <= m_max.y &&
           point.z >= m_min.z && point.z <= m_max.z;
}

bool AABB::contains(const AABB& other) const
{
    return contains(other.min()) && contains(other.max());
}
