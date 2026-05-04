#include "include/physics/3d-colliders/Sphere.hpp"

#include <math/MathUtils.hpp>

using namespace GameEngine::Physics::Bounds;


Sphere::Sphere(const Vec3& center, double radius)
    : center(center), radius(radius) {}

bool Sphere::operator!=(const Sphere& other) const
{
    return center != other.center || !isZero(radius - other.radius);
}

bool Sphere::operator==(const Sphere& other) const
{
    return center == other.center && isZero(radius - other.radius);
}

bool Sphere::contains(const Vec3& point) const
{
    return center.distSq(point) <= radius * radius;
}
