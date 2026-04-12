#pragma once

#define AFTER_COMMA_PRECISION 1e12

#include "Vec3.hpp"


namespace GameEngine::Math {

/// <summary>
/// using right hand rule (OpenGL convension)
/// </summary>
class Matrix3x3 {
public:
    enum MultiplicationOrder
    {
        XYZ,
        XZY,
        YZX,
        YXZ,
        ZXY,
        ZYX
    };

public:
    ~Matrix3x3() {};

    static Matrix3x3 identity();
    static Matrix3x3 rotateX(double radians);
    static Matrix3x3 rotateY(double radians);
    static Matrix3x3 rotateZ(double radians);

    Matrix3x3 operator*(const Matrix3x3& mat) const;
    Vec3 operator*(const Vec3& vec) const;
    static Matrix3x3 rotate(double angleX, double angleY, double angleZ,
        MultiplicationOrder order = XYZ);

private:
    Matrix3x3();
    Matrix3x3(double matrix[]);

private:
    double _matrix[9];

};
}

