#pragma once

#include <array>

#include <math/Vec2.hpp>
#include <math/Transform2.hpp>

#include "Rect.hpp"

namespace GameEngine::Physics::Bounds {
using namespace GameEngine::Math;

class OrientedRect
{
    Rect _aabb;
    std::array<Vec2, 4> _corners;

public:
    Transform2 transform;
    Vec2 size = {1,1};

    OrientedRect() = default;
    OrientedRect(const OrientedRect& other) = default;
    OrientedRect& operator=(const OrientedRect& other) = default;
    ~OrientedRect() = default;

    OrientedRect(const Vec2& pos, const Vec2& forward, const Vec2& size);
    OrientedRect(const Transform2& transform, const Vec2& size);

    bool operator!=(const OrientedRect& other) const;
    bool operator==(const OrientedRect& other) const;

    inline Vec2 left() const;
    //TODO: those should be updated automatically in the physics update step
    const Rect& AABB();
    const std::array<Vec2, 4>& corners();

    bool contains(const Vec2& point);
};

}
