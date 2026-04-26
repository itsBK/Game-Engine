#include "include/math/Transform2.hpp"

#include "include/math/Pose2.hpp"

using namespace GameEngine::Math;


Transform2::Transform2(const Vec2& pos, const Vec2& forward)
    : pos(pos), forward(forward) {}

Transform2::Transform2(const Pose2& other)
    : pos(other.pos), forward(other.dir()) {}

Transform2& Transform2::operator=(const Pose2& other)
{
    pos = other.pos;
    forward = other.dir();
    return *this;
}

bool Transform2::operator!=(const Transform2 &other) const
{
    return pos != other.pos || forward != other.forward;
}

bool Transform2::operator==(const Transform2 &other) const
{
    return pos == other.pos && forward == other.forward;
}

inline double Transform2::dist(const Vec2& other) const
{
    return pos.dist(other);
}

inline double Transform2::distSq(const Vec2& other) const
{
    return pos.distSq(other);
}

inline double Transform2::dist(const Pose2& other) const
{
    return pos.dist(other.pos);
}

inline double Transform2::distSq(const Pose2& other) const
{
    return pos.distSq(other.pos);
}

inline double Transform2::dist(const Transform2& other) const
{
    return pos.dist(other.pos);
}

inline double Transform2::distSq(const Transform2& other) const
{
    return pos.distSq(other.pos);
}

Vec2 Transform2::local(const Vec2& target) const
{
    Vec2 shifted = target - pos;
    return rotateBackward(shifted);
}

Vec2 Transform2::global(const Vec2& target) const
{
    Vec2 rotated = rotateForward(target);
    Vec2 shifted = rotated + pos;
    return shifted;
}

Transform2 Transform2::local(const Transform2& target) const
{
    Vec2 shiftedPos = target.pos - pos;
    Vec2 rotatedPos = rotateBackward(shiftedPos);
    return { rotatedPos, rotateBackward(target.forward) };
}

Transform2 Transform2::global(const Transform2& target) const
{
    Vec2 rotatedPos = rotateForward(target.pos);
    Vec2 shiftedPos = rotatedPos + pos;
    return { shiftedPos, rotateForward(target.forward) };
}

inline double Transform2::angle() const
{
    return forward.angle();
}

inline Vec2 Transform2::mirrorVec(const Vec2& target) const
{
    return forward.mirror(target);
}

inline Vec2 Transform2::mirrorPoint(const Vec2& target) const
{
    return forward.mirror(target - pos) + pos;
}

Transform2 Transform2::mirror(const Transform2& target) const
{
    return {
        forward.mirror(target.pos - pos) + pos,
        forward.mirror(target.forward)
    };
}

inline Vec2 Transform2::rotateForward(const Vec2& target) const
{
    /*
     * rotating is nothing but getting the cos and sin of an angle and
     * using the multiplication matrix to rotate a target point.
     * cos and sin of an angle are the x and y of the direction vector,
     * so we do the same multiplication without calling the expensive forward.angle() function
     */
    return {
        target.x * forward.x - target.y * forward.y,
        target.x * forward.y + target.y * forward.x
    };
}

inline Vec2 Transform2::rotateBackward(const Vec2& target) const
{
    /*
     * equivalent to using cos(-angle) and sin(-angle)
     */
    return {
        target.x * forward.x + target.y * forward.y,
        -target.x * forward.y + target.y * forward.x
    };
}

