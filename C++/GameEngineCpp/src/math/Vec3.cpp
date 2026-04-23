#include "include/math/Vec3.hpp"

#include <cmath>

using namespace GameEngine::Math;


Vec3::Vec3(double x, double y, double z)
    : x(x), y(y), z(z) {}

Vec3 Vec3::operator+(const Vec3& other) const
{
    return { x + other.x, y + other.y, z + other.z };
}

Vec3 Vec3::operator-(const Vec3& other) const
{
    return { x - other.x, y - other.y, z - other.z };
}

double Vec3::operator*(const Vec3& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::operator*(const double& scalar) const
{
    return { x * scalar, y * scalar, z * scalar };
}

Vec3 Vec3::operator/(const double& scalar) const
{
    return { x / scalar, y / scalar, z / scalar };
}

Vec3 GameEngine::Math::operator*(const double& scalar, const Vec3& vec)
{
    return vec * scalar;
}

bool Vec3::operator!=(const Vec3& other) const
{
    return !isZero(x - other.x) || !isZero(y - other.y) || !isZero(z - other.y);
}

bool Vec3::operator==(const Vec3& other) const
{
    return isZero(x - other.x) && isZero(y - other.y) && isZero(z - other.z);
}

Vec3& Vec3::operator+=(const Vec3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vec3& Vec3::operator*=(const double& scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vec3& Vec3::operator/=(const double& scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

Vec2 Vec3::xy() const
{
    return { x, y };
}

Vec2 Vec3::xz() const
{
    return { x, z };
}

Vec2 Vec3::yz() const
{
    return { y, z };
}

double Vec3::len() const
{
    return std::sqrt(x * x + y * y + z * z);
}

double Vec3::lenSq() const
{
    return x * x + y * y + z * z;
}

double Vec3::dist(const Vec3& other) const
{
    return std::sqrt((x - other.x) * (x - other.x)
                    + (y - other.y) * (y - other.y)
                    + (z - other.z) * (z - other.z));
}

double Vec3::distSq(const Vec3& other) const
{
    return (x - other.x) * (x - other.x)
        + (y - other.y) * (y - other.y)
        + (z - other.z) * (z - other.z);
}

Vec3& Vec3::norm()
{
    *this = normalized();
    return *this;
}

Vec3 Vec3::normalized() const
{
    double length = len();
    if (length != 0)
        return *this / length;

    return {};
}

Vec3 Vec3::cross(const Vec3 &other) const
{
    return {
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    };
}

double Vec3::dist(const Vec3& a, const Vec3& b)
{
    return a.dist(b);
}

double Vec3::distSq(const Vec3& a, const Vec3& b)
{
    return a.distSq(b);
}
