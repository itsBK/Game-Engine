#include "include/math/Transform2.hpp"

#include <cmath>

using namespace GameEngine::Math;


Transform2::Transform2(double x, double y, double angle)
    : pos(x, y), angle(angle) {}

Transform2::Transform2(const Vec2& pos, double angle)
    : pos(pos), angle(angle) {}

Transform2(const Pose2& other)
    : pos(other.pos), forward(other.dir()) {}

Transform2& operator=(const Pose2& other)
{
    pos = other.pos;
    forward = other.dir()
}

double Transform2::dist(const Vc2& other) const
{
    return pos.dist(other);
}

double Transform2::distSq(const Vec2& other) const
{
    return pos.distSq(other);
}

double Transform2::dist(const Transform2& other) const
{
    return pos.dist(other.pos);
}

double Transform2::distSq(const Transform2& other) const
{
    return pos.distSq(other.pos);
}


double Transform2::dist(const Pose2& other) const
{
    return pos.dist(other.pos);
}

double Transform2::distSq(const Pose2& other) const
{
    return pos.distSq(other.pos);
}

Vec2 Transform2::local(const Vec2& target) const
{
    Vec2 shifted = target - pos;
    Vec2 rotated = shifted.rotated(-angle);
    return rotated;
}

Vec2 Transform2::global(const Vec2& target) const
{
    Vec2 rotated = target.rotated(angle);
    Vec2 shifted = rotated + pos;
    return shifted;
}

Transform2 Transform2::local(const Transform2& target) const
{
    double d_angle = clampAngle(target.angle - angle);
    Vec2 shifted = target.pos - pos;
    Vec2 rotated = shifted.rotated(-angle);
    return { rotated, d_angle };
}

Transform2 Transform2::global(const Transform2& target) const
{
    double d_angle = clampAngle(target.angle + angle);
    Vec2 rotated = target.pos.rotated(angle);
    Vec2 shifted = rotated + pos;
    return { shifted, d_angle };
}

Vec2 Transform2::dir() const
{
    return Vec2::FromPolar(1, angle);
}

Vec2 Transform2::mirror(const Vec2& target) const
{
    return pos.mirror(target);
}

Transform2 Transform2::mirror(const Transform2& target) const
{
    return {
        pos.mirror(target.pos),
        2*angle - target.angle
    };
}

double Transform2::dist(const Transform2& a, const Transform2& b)
{
    return a.dist(b);
}

double Transform2::distSq(const Transform2& a, const Transform2& b)
{
    return a.distSq(b);
}

double Transform2::clampAngle(double angle)
{
    while (angle < -M_PI) angle += 2 * M_PI;
    while (angle > M_PI) angle -= 2 * M_PI;
    return angle;
}
