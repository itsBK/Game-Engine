#pragma once

#include "Vec2.hpp"

namespace GameEngine::Math {

class Vec3
{

public:
    double x = 0;
    double y = 0;
    double z = 0;

    Vec3() = default;
    Vec3(const Vec3& other) = default;
    Vec3& operator=(const Vec3& other) = default;
    ~Vec3() = default;

    Vec3(double x, double y, double z);

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    double operator*(const Vec3& other) const;

    Vec3 operator*(const double& scalar) const;
    Vec3 operator/(const double& scalar) const;

    friend Vec3 operator*(const double& scalar, const Vec3& vec);

    bool operator!=(const Vec3& other) const;
    bool operator==(const Vec3& other) const;

    Vec3& operator+=(const Vec3& other);
    Vec3& operator-=(const Vec3& other);
    Vec3& operator*=(const double& scalar);
    Vec3& operator/=(const double& scalar);

    Vec2 xy() const;
    Vec2 xz() const;
    Vec2 yz() const;

    double len() const;
    double lenSq() const;
    double dist(const Vec3& other) const;
    double distSq(const Vec3& other) const;

    /// <summary>normalize this vector and returns it</summary>
    Vec3& norm();
    /// <returns>a normalized copy of this vector</returns>
    Vec3 normalized() const;
    Vec3 cross(const Vec3& other) const;

    static double dist(const Vec3& a, const Vec3& b);
    static double distSq(const Vec3& a, const Vec3& b);

};
}

