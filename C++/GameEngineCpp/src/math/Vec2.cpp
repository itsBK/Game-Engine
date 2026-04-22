#include "include/math/Vec2.hpp"

#include <cmath>

#include "include/math/MathUtils.hpp"

using namespace GameEngine::Math;


Vec2::Vec2(double x, double y)
    : x(x), y(y) {}

Vec2 Vec2::FromPolar(double radius, double angle)
{
    return { radius * std::cos(angle), radius * std::sin(angle) };
}

Vec2 Vec2::operator+(const Vec2& other) const
{
    return { x + other.x, y + other.y };
}

Vec2 Vec2::operator-(const Vec2& other) const
{
    return { x - other.x, y - other.y };
}

double Vec2::operator*(const Vec2& other) const
{
    return x * other.x + y * other.y;
}

Vec2 Vec2::operator*(const double& scalar) const
{
    return { x * scalar, y * scalar };
}

Vec2 Vec2::operator/(const double& scalar) const
{
    return { x / scalar, y / scalar };
}

Vec2 GameEngine::Math::operator*(const double& scalar, const Vec2& vec)
{
    return vec * scalar;
}

bool Vec2::operator!=(const Vec2& other) const
{
    return !isZero(x - other.x) || !isZero(y - other.y);
}

bool Vec2::operator==(const Vec2& other) const
{
    return isZero(x - other.x) && isZero(y - other.y);
}

Vec2& Vec2::operator+=(const Vec2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2& Vec2::operator*=(const double& scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2& Vec2::operator/=(const double& scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

Vec2 Vec2::operator>>(const Vec2& other) const
{
    double lengthSq = other.lenSq();
    if (isZero(lengthSq))
        return {};
    double length = *this * other / lengthSq;
    return other * length;
}

double Vec2::len() const
{
    return std::sqrt(x * x + y * y);
}

double Vec2::lenSq() const
{
    return x * x + y * y;
}

double Vec2::dist(const Vec2& other) const
{
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

double Vec2::distSq(const Vec2& other) const
{
    return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
}

double Vec2::angle() const
{
    return std::atan2(y, x);
}

Vec2& Vec2::norm()
{
    *this = normalized();
    return *this;
}

Vec2 Vec2::normalized() const
{
    double length = len();
    if (!isZero(length))
        return *this / length;

    return {};
}

double Vec2::dot(const Vec2& other) const
{
    return *this * other;
}

double Vec2::cross(const Vec2& other) const
{
    return x * other.y - y * other.x;
}

Vec2& Vec2::rotate(double angle)
{
    *this = rotated(angle);
    return *this;
}

Vec2 Vec2::rotated(double angle) const
{
    double c = std::cos(angle);
    double s = std::sin(angle);

    return {
        x * c - y * s,
        x * s + y * c
    };
}

Vec2 Vec2::mirror(const Vec2& target) const
{
    Vec2 projected = target >> *this;
    return (projected *= 2) -= target;
}

double Vec2::dist(const Vec2& a, const Vec2& b)
{
    return a.dist(b);
}

double Vec2::distSq(const Vec2& a, const Vec2& b)
{
    return a.distSq(b);
}
