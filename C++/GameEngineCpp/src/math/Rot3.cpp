#include "include/math/Rot3.hpp"

using namespace GameEngine::Math;


Rot3::Rot3(double r, double p, double y)
    : roll(r), pitch(p), yaw(y) {}

Rot3::Rot3(const Vec3 &other)
    : roll(other.x), pitch(other.y), yaw(other.z) {}

Rot3& Rot3::operator=(const Vec3 &other)
{
    roll = other.x;
    pitch = other.y;
    yaw = other.z;
    return *this;
}
