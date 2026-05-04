#include "include/physics/2d-colliders/OrientedRect.hpp"

#include <cmath>

using namespace GameEngine::Physics::Bounds;


OrientedRect::OrientedRect(const Vec2& pos, const Vec2& forward, const Vec2& size)
    : transform(pos, forward), size(size) {}

OrientedRect::OrientedRect(const Transform2& transform, const Vec2& size)
    : transform(transform), size(size) {}

bool OrientedRect::operator!=(const OrientedRect& other) const
{
    return transform != other.transform || size != other.size;
}

bool OrientedRect::operator==(const OrientedRect& other) const
{
    return transform == other.transform && size == other.size;
}

bool OrientedRect::contains(const Vec2& point)
{
    if (!calcAABB().contains(point))
        return false;

    Vec2 local0 = transform.local(point);
    return std::abs(local0.x) <= size.x * 0.5
        && std::abs(local0.y) <= size.y * 0.5;
}

const Rect& OrientedRect::calcAABB()
{
    Vec2 front = transform.forward * (size.x * 0.5);
    Vec2 left0 = transform.left() * (size.y * 0.5);

    Vec2 corner0 = left0 + front;
    Vec2 corner1 = left0 - front;

    _aabb.center = transform.pos;
    _aabb.size.x = 2 * std::max(std::abs(corner0.x), std::abs(corner1.x));
    _aabb.size.y = 2 * std::max(std::abs(corner0.y), std::abs(corner1.y));
    return _aabb;
}

const std::array<Vec2, 4>& OrientedRect::corners()
{
    Vec2 front = transform.forward * (size.x * 0.5);
    Vec2 left0 = transform.left() * (size.y * 0.5);

    _corners[0] = transform.pos + left0 + front;
    _corners[1] = transform.pos + left0 - front;
    _corners[2] = transform.pos - left0 - front;
    _corners[3] = transform.pos - left0 + front;
    return _corners;
}
