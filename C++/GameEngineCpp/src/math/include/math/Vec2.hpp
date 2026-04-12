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
    /// dot product
    double operator*(const Vec2& other) const;

    Vec2 operator*(const double& scalar) const;
    Vec2 operator/(const double& scalar) const;

    friend Vec2 operator*(const double& scalar, const Vec2& vec);

    Vec2& operator+=(const Vec2& other);
    Vec2& operator-=(const Vec2& other);

    Vec2& operator*=(const double& scalar);
    Vec2& operator/=(const double& scalar);
    /// project this onto other
    Vec2 operator>>(const Vec2& other) const;

    double len() const;
    double lenSq() const;
    double dist(const Vec2& other) const;
    double distSq(const Vec2& other) const;

    double angle() const;
    /// normalize this vector
    /// @return reference to self
    Vec2& norm();
    /// @return a normalized copy of this vector
    Vec2 normalized() const;
    double dot(const Vec2& other) const;
    double cross(const Vec2& other) const;
    /// rotate this vector
    /// @return reference to self
    Vec2& rotate(double angle);
    /// @return a rotated copy of this vector
    Vec2 rotated(double angle) const;
    /// mirror target over this pose
    Vec2 mirror(const Vec2& target) const;

    static double dist(const Vec2& a, const Vec2& b);
    static double distSq(const Vec2& a, const Vec2& b);
};

}
