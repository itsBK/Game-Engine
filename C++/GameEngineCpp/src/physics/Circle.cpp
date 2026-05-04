#include "include/physics/2d-colliders/Circle.hpp"

#include <math/MathUtils.hpp>

using namespace GameEngine::Physics::Bounds;


Circle::Circle(const Vec2& center, double radius)
    : center(center), radius(radius) {}

bool Circle::operator!=(const Circle& other) const
{
    return center != other.center || !isZero(radius - other.radius);
}

bool Circle::operator==(const Circle& other) const
{
    return center == other.center && isZero(radius - other.radius);
}

bool Circle::contains(const Vec2& point) const
{
    return center.distSq(point) <= radius * radius;
}
