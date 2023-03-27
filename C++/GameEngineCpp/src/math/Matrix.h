#pragma once

#include "Vector3.h"

#define AFTER_COMMA_PRECISION 1000000000

namespace GameEngine {
namespace Math {

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
    static Matrix3x3 rotateX(const double radians);
    static Matrix3x3 rotateY(const double radians);
    static Matrix3x3 rotateZ(const double radians);

    Matrix3x3 operator*(const Matrix3x3& mat);
    Vector3 operator*(const Vector3& vec);
    static Matrix3x3 rotate(double angleX, double angleY, double angleZ,
        MultiplicationOrder order = XYZ);

private:
    Matrix3x3();
    Matrix3x3(double matrix[]);

private:
    double _matrix[9];

};
}
}
