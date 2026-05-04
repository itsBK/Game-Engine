#include "include/physics/3d-colliders/OBB.hpp"

#include <cmath>

using namespace GameEngine::Physics::Bounds;


OBB::OBB(const Vec3& pos, const Vec3& forward, const Vec3& left, const Vec3& size)
    : transform(pos, forward, left), size(size) {}

OBB::OBB(const Transform3& transform, const Vec3& size)
    : transform(transform), size(size) {}

bool OBB::operator!=(const OBB& other) const
{
    return transform != other.transform || size != other.size;
}

bool OBB::operator==(const OBB& other) const
{
    return transform == other.transform && size == other.size;
}

bool OBB::contains(const Vec3& point)
{
    if (!calcAABB().contains(point))
        return false;

    Vec3 local0 = transform.local(point);

    return std::abs(local0.x) <= size.x * 0.5
        && std::abs(local0.y) <= size.y * 0.5
        && std::abs(local0.z) <= size.z * 0.5;
}

const AABB& OBB::calcAABB()
{
    Vec3 f = transform.forward * (size.x * 0.5);
    Vec3 l = transform.left * (size.y * 0.5);
    Vec3 u = transform.up() * (size.z * 0.5);

    Vec3 corner0 = transform.pos + u + l + f;
    Vec3 corner1 = transform.pos + u + l - f;
    Vec3 corner2 = transform.pos + u - l - f;
    Vec3 corner3 = transform.pos + u - l + f;

    _aabb.center = transform.pos;
    _aabb.size.x = 2 * std::max(std::max(std::abs(corner0.x), std::abs(corner1.x)),
                                std::max(std::abs(corner2.x), std::abs(corner3.x)));
    _aabb.size.y = 2 * std::max(std::max(std::abs(corner0.y), std::abs(corner1.y)),
                                std::max(std::abs(corner2.y), std::abs(corner3.y)));
    _aabb.size.z = 2 * std::max(std::max(std::abs(corner0.z), std::abs(corner1.z)),
                                std::max(std::abs(corner2.z), std::abs(corner3.z)));
    return _aabb;
}

const std::array<Vec3, 8>& OBB::corners()
{
    Vec3 f = transform.forward * size.x * 0.5;
    Vec3 l = transform.left * size.y * 0.5;
    Vec3 u = transform.up() * size.z * 0.5;

    _corners[0] = transform.pos + u + l + f;
    _corners[1] = transform.pos + u + l - f;
    _corners[2] = transform.pos + u - l - f;
    _corners[3] = transform.pos + u - l + f;
    _corners[4] = transform.pos - u - l + f;
    _corners[5] = transform.pos - u - l - f;
    _corners[6] = transform.pos - u + l - f;
    _corners[7] = transform.pos - u + l + f;
    return _corners;
}
