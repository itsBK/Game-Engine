#pragma once

#include <math/Vec2.hpp>

namespace GameEngine::Physics::Bounds {
using namespace GameEngine::Math;

class Circle
{
public:
    Vec2 center = {};
    double radius = 0.5;

    Circle() = default;
    Circle(const Circle& other) = default;
    Circle& operator=(const Circle& other) = default;
    ~Circle() = default;

    Circle(const Vec2& center, double radius);

    bool operator!=(const Circle& other) const;
    bool operator==(const Circle& other) const;

    bool contains(const Vec2& point) const;
};

}
