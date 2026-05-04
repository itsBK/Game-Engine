#pragma once

#include <math/Vec3.hpp>

namespace GameEngine::Physics::Bounds {
using namespace GameEngine::Math;

class Sphere
{
public:
    Vec3 center = {};
    double radius = 0.5;

    Sphere() = default;
    Sphere(const Sphere& other) = default;
    Sphere& operator=(const Sphere& other) = default;
    ~Sphere() = default;

    Sphere(const Vec3& center, double radius);

    bool operator!=(const Sphere& other) const;
    bool operator==(const Sphere& other) const;

    bool contains(const Vec3& point) const;
};

}
