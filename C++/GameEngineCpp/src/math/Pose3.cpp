#include "include/math/Pose3.hpp"

using namespace GameEngine::Math;


Pose3::Pose3(const Vec3& pos, const Rot3& rot)
    : pos(pos), rot(rot) {}

Pose2 Pose3::xy() const
{
    return { pos.xy(), rot.yaw };
}

Pose2 Pose3::xz() const
{
    return { pos.xz(), rot.pitch };
}

Pose2 Pose3::yz() const
{
    return { pos.yz(), rot.roll };
}

double Pose3::dist(const Vec3& other) const
{
    return pos.dist(other);
}

double Pose3::distSq(const Vec3& other) const
{
    return pos.distSq(other);
}

double Pose3::dist(const Pose3& other) const
{
    return pos.dist(other.pos);
}

double Pose3::distSq(const Pose3& other) const
{
    return pos.distSq(other.pos);
}

double Pose3::dist(const Pose3& a, const Pose3& b)
{
    return a.dist(b);
}

double Pose3::distSq(const Pose3& a, const Pose3& b)
{
    return a.distSq(b);
}
