#pragma once

#include <math/Vec2.hpp>

namespace GameEngine::Physics::Bounds {
using namespace GameEngine::Math;

class Rect
{
public:
    Vec2 center = {};
    Vec2 size = {1, 1};

    Rect() = default;
    Rect(const Rect& other) = default;
    Rect& operator=(const Rect& other) = default;
    ~Rect() = default;

    Rect(const Vec2& center, const Vec2& size);
    Rect(const Vec2& min, const Vec2& max, bool isMinMax);

    bool operator!=(const Rect& other) const;
    bool operator==(const Rect& other) const;

    inline Vec2 min() const;
    inline Vec2 max() const;

    bool contains(const Vec2& point) const;
    bool contains(const Rect& other) const;
};

}
