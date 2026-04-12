#include "include/math/Pose2.hpp"

#include <cmath>

using namespace GameEngine::Math;


Pose2::Pose2(double x, double y, double angle)
    : pos(x, y), angle(angle) {}

Pose2::Pose2(const Vec2& pos, double angle)
    : pos(pos), angle(angle) {}

double Pose2::dist(const Vec2& other) const
{
    return pos.dist(other);
}

double Pose2::distSq(const Vec2& other) const
{
    return pos.distSq(other);
}

double Pose2::dist(const Pose2& other) const
{
    return pos.dist(other.pos);
}

double Pose2::distSq(const Pose2& other) const
{
    return pos.distSq(other.pos);
}

Vec2 Pose2::local(const Vec2& target) const
{
    Vec2 shifted = target - pos;
    Vec2 rotated = shifted.rotated(-angle);
    return rotated;
}

Vec2 Pose2::global(const Vec2& target) const
{
    Vec2 rotated = target.rotated(angle);
    Vec2 shifted = rotated + pos;
    return shifted;
}

Pose2 Pose2::local(const Pose2& target) const
{
    double d_angle = clampAngle(target.angle - angle);
    Vec2 shifted = target.pos - pos;
    Vec2 rotated = shifted.rotated(-angle);
    return { rotated, d_angle };
}

Pose2 Pose2::global(const Pose2& target) const
{
    double d_angle = clampAngle(target.angle + angle);
    Vec2 rotated = target.pos.rotated(angle);
    Vec2 shifted = rotated + pos;
    return { shifted, d_angle };
}

Vec2 Pose2::dir() const
{
    return Vec2::FromPolar(1, angle);
}

Vec2 Pose2::mirror(const Vec2& target) const
{
    return pos.mirror(target);
}

Pose2 Pose2::mirror(const Pose2& target) const
{
    return {
        pos.mirror(target.pos),
        2*angle - target.angle
    };
}

double Pose2::dist(const Pose2& a, const Pose2& b)
{
    return a.dist(b);
}

double Pose2::distSq(const Pose2& a, const Pose2& b)
{
    return a.distSq(b);
}

double Pose2::clampAngle(double angle)
{
    while (angle < -M_PI) angle += 2 * M_PI;
    while (angle > M_PI) angle -= 2 * M_PI;
    return angle;
}
