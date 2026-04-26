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
    Vec3 operator*(const double& scalar) const;
    Vec3 operator/(const double& scalar) const;
    /// @return the dot product.
    inline double operator*(const Vec3& other) const;

    friend inline Vec3 operator*(const double& scalar, const Vec3& vec);

    bool operator!=(const Vec3& other) const;
    bool operator==(const Vec3& other) const;

    /// @return a reference to self
    Vec3& operator+=(const Vec3& other);
    /// @return a reference to self
    Vec3& operator-=(const Vec3& other);
    /// @return a reference to self
    Vec3& operator*=(const double& scalar);
    /// @return a reference to self
    Vec3& operator/=(const double& scalar);
    /// project this vector onto other.
    Vec3 operator>>(const Vec3& other) const;

    Vec2 xy() const;
    Vec2 xz() const;
    Vec2 yz() const;

    double len() const;
    double lenSq() const;
    double dist(const Vec3& other) const;
    double distSq(const Vec3& other) const;

    /// normalize this vector
    /// @return reference to self
    Vec3& norm();
    /// @return a normalized copy of this
    Vec3 normalized() const;
    double dot(const Vec3& other) const;
    Vec3 cross(const Vec3& other) const;
    /// mirror target over this vector
    Vec3 mirror(const Vec3& target) const;
};

}

