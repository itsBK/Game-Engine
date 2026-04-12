#pragma once

#include "Pose2.hpp"
#include "Vec3.hpp"
#include "Rot3.hpp"

namespace GameEngine::Math {

class Pose3
{

public:
    Vec3 pos = {};
    /// all ranged between [-PI, PI]
    Rot3 rot = {};

    Pose3() = default;
    Pose3(const Pose3& other) = default;
    Pose3& operator=(const Pose3& other) = default;
    ~Pose3() = default;

    Pose3(const Vec3& pos, const Rot3& rot);

    /// @return xy with yaw as angle
    Pose2 xy() const;
    /// @return xz with pitch as angle
    Pose2 xz() const;
    /// @return yz with roll as angle
    Pose2 yz() const;

    double dist(const Vec3& other) const;
    double distSq(const Vec3& other) const;
    double dist(const Pose3& other) const;
    double distSq(const Pose3& other) const;

    static double dist(const Pose3& a, const Pose3& b);
    static double distSq(const Pose3& a, const Pose3& b);

};

}
