#pragma once

#include "Vec2.hpp"

namespace GameEngine::Math {
class Pose2;

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
    explicit Transform2(const Pose2& other);
    Transform2& operator=(const Pose2& other);

    bool operator!=(const Transform2& other) const;
    bool operator==(const Transform2& other) const;

    inline double dist(const Vec2& other) const;
    inline double distSq(const Vec2& other) const;
    inline double dist(const Pose2& other) const;
    inline double distSq(const Pose2& other) const;
    inline double dist(const Transform2& other) const;
    inline double distSq(const Transform2& other) const;

    /// @return local to global transformation
    Vec2 local(const Vec2& target) const;
    /// @return global to local transformation
    Vec2 global(const Vec2& target) const;
    /// @return local to global transformation
    Transform2 local(const Transform2& target) const;
    /// @return global to local transformation
    Transform2 global(const Transform2& target) const;

    /// angle of the forward vector
    inline double angle() const;

    /// mirror target over this transform
    inline Vec2 mirrorVec(const Vec2& target) const;
    /// mirror target over this transform
    inline Vec2 mirrorPoint(const Vec2& target) const;
    /// mirror target over this transform
    Transform2 mirror(const Transform2& target) const;

private:
    inline Vec2 rotateForward(const Vec2& target) const;
    inline Vec2 rotateBackward(const Vec2& target) const;
};

}
