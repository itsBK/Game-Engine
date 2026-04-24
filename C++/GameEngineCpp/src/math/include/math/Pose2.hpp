#pragma once

#include "Vec2.hpp"

namespace GameEngine::Math {

class Pose2
{

public:
    Vec2 pos = {};
    /// usually yaw, ranged between [-PI, PI]
    double angle = 0;

    Pose2() = default;
    Pose2(const Pose2& other) = default;
    Pose2& operator=(const Pose2& other) = default;
    ~Pose2() = default;

    Pose2(double x, double y, double angle);
    Pose2(const Vec2& pos, double angle);
    Pose2(const Transform2& other);
    Pose2& operator=(const Transform2& other);

    double dist(const Vec2& other) const;
    double distSq(const Vec2& other) const;
    double dist(const Pose2& other) const;
    double distSq(const Pose2& other) const;
    double dist(const Transform2& other) const;
    double distSq(const Transform2& other) const;

    /// @return local to global transformation
    Vec2 local(const Vec2& target) const;
    /// @return global to local transformation
    Vec2 global(const Vec2& target) const;
    /// @return local to global transformation
    Pose2 local(const Pose2& target) const;
    /// @return global to local transformation
    Pose2 global(const Pose2& target) const;

    Vec2 dir() const;

    /// mirror target over this pose
    Vec2 mirror(const Vec2& target) const;
    /// mirror target over this pose
    Pose2 mirror(const Pose2& target) const;

    static double dist(const Pose2& a, const Pose2& b);
    static double distSq(const Pose2& a, const Pose2& b);

private:
    static double clampAngle(double angle) ;
};

}
