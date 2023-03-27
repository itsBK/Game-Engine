#pragma once

#include <math.h>

namespace GameEngine {
namespace Math {

class Vector3 {

public:
    Vector3();
    Vector3(double x, double y, double z);
    Vector3(const Vector3& other);
    ~Vector3() {};

    Vector3 operator=(const Vector3& other);
    Vector3 operator+(const Vector3& other);
    Vector3 operator-(const Vector3& other);
    Vector3 operator+(const double scalar);
    Vector3 operator-(const double scalar);
    Vector3 operator*(const double scalar);
    Vector3 operator/(const double scalar);

    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3& operator+=(const double scalar);
    Vector3& operator-=(const double scalar);
    Vector3& operator*=(const double scalar);
    Vector3& operator/=(const double scalar);

    Vector3 copy();

    double length();
    double lengthSq();

    /// <summary>normalize this vector and returns it</summary>
    Vector3* normalize();
    /// <returns>a normalized copy of this vector</returns>
    Vector3 normalized();

    // Vector3* rotate(double angle, double axisX, double axisY, double axisZ);

    double distance(Vector3 other);
    double distanceSq(Vector3 other);
    static double distance(Vector3& a, Vector3& b);
    static double distanceSq(Vector3& a, Vector3& b);

public:
    double x = 0;
    double y = 0;
    double z = 0;

};
}
}
