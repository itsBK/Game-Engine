#pragma once

namespace GameEngine::Math {

class Vec2
{

public:
    double x = 0;
    double y = 0;

    Vec2() = default;
    Vec2(const Vec2& other) = default;
    Vec2& operator=(const Vec2& other) = default;
    ~Vec2() = default;

    Vec2(double x, double y);
    static Vec2 FromPolar(double radius, double angle);

    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;
    Vec2 operator*(const double& scalar) const;
    Vec2 operator/(const double& scalar) const;
    /// @return the dot product.
    inline double operator*(const Vec2& other) const;

    friend inline Vec2 operator*(const double& scalar, const Vec2& vec);

    bool operator!=(const Vec2& other) const;
    bool operator==(const Vec2& other) const;

    /// @return a reference to self
    Vec2& operator+=(const Vec2& other);
    /// @return a reference to self
    Vec2& operator-=(const Vec2& other);
    /// @return a reference to self
    Vec2& operator*=(const double& scalar);
    /// @return a reference to self
    Vec2& operator/=(const double& scalar);
    /// project this vector onto other.
    Vec2 operator>>(const Vec2& other) const;

    double len() const;
    double lenSq() const;
    double dist(const Vec2& other) const;
    double distSq(const Vec2& other) const;

    /// in radians.
    double angle() const;
    /// normalize this vector
    /// @return reference to self
    Vec2& norm();
    /// @return a normalized copy of this
    Vec2 normalized() const;
    double dot(const Vec2& other) const;
    /// @return the 2D cross product (z-component).
    double cross(const Vec2& other) const;
    /// rotates the vector in-place by the given angle (radians).
    /// @return a reference to self
    Vec2& rotate(double angle);
    /// @return a rotated copy of this
    Vec2 rotated(double angle) const;
    /// mirror target over this vector
    Vec2 mirror(const Vec2& target) const;
    /// @return the perpendicular vector on this one, rotated 90° CCW
    inline Vec2 perp() const;
};

}
