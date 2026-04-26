#include "include/math/Transform3.hpp"

using namespace GameEngine::Math;


Transform3::Transform3(const Vec3& pos, const Vec3& forward, const Vec3& left)
    : pos(pos), forward(forward.normalized()), left(left.normalized()) {}

bool Transform3::operator!=(const Transform3 &other) const
{
    return pos != other.pos || forward != other.forward || left != other.left;
}

bool Transform3::operator==(const Transform3 &other) const
{
    return pos == other.pos && forward == other.forward && left == other.left;
}

inline double Transform3::dist(const Vec3& other) const
{
    return pos.dist(other);
}

inline double Transform3::distSq(const Vec3& other) const
{
    return pos.distSq(other);
}

inline double Transform3::dist(const Transform3& other) const
{
    return pos.dist(other.pos);
}

inline double Transform3::distSq(const Transform3& other) const
{
    return pos.distSq(other.pos);
}

Vec3 Transform3::local(const Vec3& target) const
{
    Vec3 shifted = target - pos;
    return rotateBackward(shifted);
}

Vec3 Transform3::global(const Vec3& target) const
{
    Vec3 rotated = rotateForward(target);
    Vec3 shifted = rotated + pos;
    return shifted;
}

Transform3 Transform3::local(const Transform3& target) const
{
    Vec3 shiftedPos = target.pos - pos;
    Vec3 rotatedPos = rotateBackward(shiftedPos);
    return { rotatedPos, rotateBackward(target.forward), rotateBackward(target.left) };
}

Transform3 Transform3::global(const Transform3& target) const
{
    Vec3 rotatedPos = rotateForward(target.pos);
    Vec3 shiftedPos = rotatedPos + pos;
    return { shiftedPos, rotateForward(target.forward), rotateForward(target.left) };
}

inline Vec3 Transform3::up() const
{
    return forward.cross(left);
}

inline Vec3 Transform3::mirrorVec(const Vec3& target) const
{
    return forward.mirror(target);
}

inline Vec3 Transform3::mirrorPoint(const Vec3& target) const
{
    return forward.mirror(target - pos) + pos;
}

Transform3 Transform3::mirror(const Transform3& target) const
{
    return {
        forward.mirror(target.pos - pos) + pos,
        forward.mirror(target.forward),
        forward.mirror(target.left)
    };
}

inline Vec3 Transform3::rotateForward(const Vec3& target) const
{
    /*
     * rotating is applying the rotation matrix to the target.
     * the rotation matrix is built with forward(x), left(y), up(z), each represents a column.
     */
    Vec3 u = up();
    return {
        target.x * forward.x + target.y * left.x + target.z * u.x,
        target.x * forward.y + target.y * left.y + target.z * u.y,
        target.x * forward.z + target.y * left.z + target.z * u.z
    };
}

inline Vec3 Transform3::rotateBackward(const Vec3& target) const
{
    /*
     * rotating back is applying the transposed rotation matrix to the target.
     * the rotation matrix is built with forward(x), left(y), up(z), each represents a column.
     * so the transpose of that is each vector representing a row.
     * multiplication is then just the dot product
     */
    Vec3 u = up();
    return {
        target.dot(forward),
        target.dot(left),
        target.dot(u)
    };
}
