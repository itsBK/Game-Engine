#include "include/physics/2d-colliders/Rect.hpp"

using namespace GameEngine::Physics::Bounds;


Rect::Rect(const Vec2& center, const Vec2& size)
    : center(center), size(size) {}

Rect::Rect(const Vec2& min, const Vec2& max, bool /*isMinMax*/)
    : center((min + max) * 0.5), size(max - min) {}

bool Rect::operator!=(const Rect& other) const
{
    return center != other.center || size != other.size;
}

bool Rect::operator==(const Rect& other) const
{
    return center == other.center && size == other.size;
}

inline Vec2 Rect::min() const
{
    return center - size * 0.5;
}

inline Vec2 Rect::max() const
{
    return center + size * 0.5;
}

bool Rect::contains(const Vec2& point) const
{
    Vec2 m = min();
    Vec2 mx = max();
    return point.x >= m.x && point.x <= mx.x &&
           point.y >= m.y && point.y <= mx.y;
}

bool Rect::contains(const Rect& other) const
{
    return contains(other.min()) && contains(other.max());
}
