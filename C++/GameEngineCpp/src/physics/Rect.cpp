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

void Rect::update(const Transform2& transform, const Vec2& offset)
{
    center = transform.pos + offset;
    m_min = center - size * 0.5;
    m_max = center + size * 0.5;
}

const Vec2& Rect::min() const
{
    return m_min;
}

const Vec2& Rect::max() const
{
    return m_max;
}

bool Rect::contains(const Vec2& point) const
{
    return point.x >= m_min.x && point.x <= m_max.x &&
           point.y >= m_min.y && point.y <= m_max.y;
}

bool Rect::contains(const Rect& other) const
{
    return contains(other.m_min) && contains(other.m_max);
}
