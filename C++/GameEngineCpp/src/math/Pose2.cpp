#include "include/math/Pose2.hpp"

#include "include/math/Transform2.hpp"
#include "include/math/MathUtils.hpp"

using namespace GameEngine::Math;


Pose2::Pose2(double x, double y, double angle)
    : pos(x, y), angle(angle) {}

Pose2::Pose2(const Vec2& pos, double angle)
    : pos(pos), angle(angle) {}

Pose2::Pose2(const Transform2& other)
    : pos(other.pos), angle(other.angle()) {}

Pose2& Pose2::operator=(const Transform2& other)
{
    pos = other.pos;
    angle = other.angle();
    return *this;
}

bool Pose2::operator!=(const Pose2 &other) const
{
    return pos != other.pos || !isZero(angle - other.angle);
}

bool Pose2::operator==(const Pose2 &other) const
{
    return pos == other.pos && isZero(angle - other.angle);
}

inline double Pose2::dist(const Vec2& other) const
{
    return pos.dist(other);
}

inline double Pose2::distSq(const Vec2& other) const
{
    return pos.distSq(other);
}

inline double Pose2::dist(const Pose2& other) const
{
    return pos.dist(other.pos);
}

inline double Pose2::distSq(const Pose2& other) const
{
    return pos.distSq(other.pos);
}

inline double Pose2::dist(const Transform2& other) const
{
    return pos.dist(other.pos);
}

inline double Pose2::distSq(const Transform2& other) const
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

inline Vec2 Pose2::dir() const
{
    return Vec2::FromPolar(1, angle);
}

inline Vec2 Pose2::mirrorVec(const Vec2& target) const
{
    return dir().mirror(target);
}

inline Vec2 Pose2::mirrorPoint(const Vec2& target) const
{
    return dir().mirror(target - pos) + pos;
}

Pose2 Pose2::mirror(const Pose2& target) const
{
    return {
        dir().mirror(target.pos - pos) + pos,
        2*angle - target.angle
    };
}
