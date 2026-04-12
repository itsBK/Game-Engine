#pragma once

#include "Vec3.hpp"

namespace GameEngine::Math {

class Rot3
{
public:
    /// (around x-axes)
    double roll = 0;
    /// (around y-axes)
    double pitch = 0;
    /// (around z-axes)
    double yaw = 0;

    Rot3() = default;
    Rot3(const Rot3& other) = default;
    Rot3& operator=(const Rot3& other) = default;
    ~Rot3() = default;

    ///
    /// @param r rotate around X
    /// @param p rotate around Y
    /// @param y rotate around Z
    Rot3(double r, double p, double y);
    Rot3(const Vec3& other);
    Rot3& operator=(const Vec3& other);
};

}
