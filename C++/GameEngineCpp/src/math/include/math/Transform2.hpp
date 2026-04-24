#pragma once

#include "Vec2.hpp"

namespace GameEngine::Math {

class Transform2
{

public:
    Vec2 pos = {};
    /// unit Vector
    Vec2 forward = {};

    Transform2() = default;
    Transform2(const Transform2& other) = default;
    Transform2& operator=(const Transform2& other) = default;
    ~Transform2() = default;

    Transform2(const Vec2& pos, const Vec2& forward);
    Transform2(const Pose2& other);
    Transform2& operator=(const Pose2& other);

    double dist(const Vec2& other) const;
    double distSq(const Vec2& other) const;
    double dist(const Transform2& other) const;
    double distSq(const Transform2& other) const;
    double dist(const Pose2& other) const;
    double distSq(const Pose2& other) const;

    /// @return local to global transformation
    Vec2 local(const Vec2& target) const;
    /// @return global to local transformation
    Vec2 global(const Vec2& target) const;
    /// @return local to global transformation
    Transform2 local(const Transform2& target) const;
    /// @return global to local transformation
    Transform2 global(const Transform2& target) const;

    /// angle of the forward vector
    double angle() const;

    /// mirror target over this transform
    Vec2 mirror(const Vec2& target) const;
    /// mirror target over this transform
    Transform2 mirror(const Transform2& target) const;

    static double dist(const Transform2& a, const Transform2& b);
    static double distSq(const Transform2& a, const Transform2& b);
};

}
