#pragma once

#include <array>

#include "Vec3.hpp"

namespace GameEngine::Math {

///
/// using right hand rule (OpenGL convention)
class Matrix3x3 {

    double _matrix[9] = {};
    explicit inline Matrix3x3(const std::array<double, 9>& matrix);

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
    class Row
    {
    public:
        explicit Row(double* matrix, const unsigned int& rowNum);
        double& operator[](const unsigned int& index);
    private:
        unsigned int _rowNum;
        double* _matrix;
    };

    Matrix3x3() = default;
    Matrix3x3(const Matrix3x3& other) = default;
    Matrix3x3& operator=(const Matrix3x3& other) = default;
    ~Matrix3x3() = default;

    Matrix3x3(const Vec3& row1, const Vec3& row2, const Vec3& row3);

    Row operator[](const unsigned int& row);
    /// @return the transpose of this matrix
    Matrix3x3 T() const;

    static Matrix3x3 identity();
    static Matrix3x3 rotateX(double radians);
    static Matrix3x3 rotateY(double radians);
    static Matrix3x3 rotateZ(double radians);

    Matrix3x3 operator*(const Matrix3x3& other) const;
    Vec3 operator*(const Vec3& other) const;

    /// in radian
    static Matrix3x3 rotate(double angleX, double angleY, double angleZ,
        MultiplicationOrder order = ZYX);
};

}

