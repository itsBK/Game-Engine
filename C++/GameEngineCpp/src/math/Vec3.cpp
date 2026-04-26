#include "include/math/Vec3.hpp"

#include <cmath>

#include "include/math/MathUtils.hpp"

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

Vec3 Vec3::operator*(const double& scalar) const
{
    return { x * scalar, y * scalar, z * scalar };
}

Vec3 Vec3::operator/(const double& scalar) const
{
    return { x / scalar, y / scalar, z / scalar };
}

inline double Vec3::operator*(const Vec3& other) const
{
    return dot(other);
}

Vec3 inline GameEngine::Math::operator*(const double& scalar, const Vec3& vec)
{
    return vec * scalar;
}

bool Vec3::operator!=(const Vec3& other) const
{
    return !isZero(x - other.x) || !isZero(y - other.y) || !isZero(z - other.z);
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

Vec3 Vec3::operator>>(const Vec3& other) const
{
    double lengthSq = other.lenSq();
    if (isZero(lengthSq))
        return {};

    double length = *this * other / lengthSq;
    return other * length;
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

double Vec3::dot(const Vec3& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3 &other) const
{
    return {
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    };
}

Vec3 Vec3::mirror(const Vec3& target) const
{
    Vec3 projected = target >> *this;
    return (projected *= 2) -= target;
}
