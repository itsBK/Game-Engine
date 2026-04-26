#include "include/math/Matrix3x3.hpp"

#include <cmath>

#include "include/math/MathUtils.hpp"

using namespace GameEngine::Math;

inline Matrix3x3::Matrix3x3(const std::array<double, 9>& matrix)
	: _matrix {
		matrix[0], matrix[1], matrix[2],
		matrix[3], matrix[4], matrix[5],
		matrix[6], matrix[7], matrix[8]
	} {}

Matrix3x3::Matrix3x3(const Vec3& row1, const Vec3& row2, const Vec3& row3)
	: _matrix {
		row1.x, row1.y, row1.z,
		row2.x, row2.y, row2.z,
		row3.x, row3.y, row3.z,
	} {}

Matrix3x3::Row::Row(double* matrix, const unsigned int& rowNum)
{
	_matrix = matrix;
	_rowNum = rowNum;
}

double& Matrix3x3::Row::operator[](const unsigned int& col)
{
	return _matrix[3 * _rowNum + col];
}

Matrix3x3::Row Matrix3x3::operator[](const unsigned int& row)
{
	return Row(_matrix, row);
}

Matrix3x3 Matrix3x3::T() const
{
	return Matrix3x3({
		_matrix[0], _matrix[3], _matrix[6],
		_matrix[1], _matrix[4], _matrix[7],
		_matrix[2], _matrix[5], _matrix[8]
	});
}

Matrix3x3 Matrix3x3::identity()
{
	return Matrix3x3({
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	});
}

Matrix3x3 Matrix3x3::rotateX(double radians) {
	double c = cos(radians);
	double s = sin(radians);
	return Matrix3x3({
		1, 0,  0,
		0, c, -s,
		0, s,  c
	});
}

Matrix3x3 Matrix3x3::rotateY(const double radians) {
	double c = cos(radians);
	double s = sin(radians);
	return Matrix3x3({
		 c,  0, s,
		 0,  1, 0,
		-s,  0, c
	});
}

Matrix3x3 Matrix3x3::rotateZ(const double radians) {
	double c = cos(radians);
	double s = sin(radians);
	return Matrix3x3({
		c, -s, 0,
		s,  c, 0,
		0,  0, 1
	});
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& mat) const
{
	return Matrix3x3({
		_matrix[0] * mat._matrix[0] + _matrix[1] * mat._matrix[3] + _matrix[2] * mat._matrix[6],
		_matrix[0] * mat._matrix[1] + _matrix[1] * mat._matrix[4] + _matrix[2] * mat._matrix[7],
		_matrix[0] * mat._matrix[2] + _matrix[1] * mat._matrix[5] + _matrix[2] * mat._matrix[8],

		_matrix[3] * mat._matrix[0] + _matrix[4] * mat._matrix[3] + _matrix[5] * mat._matrix[6],
		_matrix[3] * mat._matrix[1] + _matrix[4] * mat._matrix[4] + _matrix[5] * mat._matrix[7],
		_matrix[3] * mat._matrix[2] + _matrix[4] * mat._matrix[5] + _matrix[5] * mat._matrix[8],

		_matrix[6] * mat._matrix[0] + _matrix[7] * mat._matrix[3] + _matrix[8] * mat._matrix[6],
		_matrix[6] * mat._matrix[1] + _matrix[7] * mat._matrix[4] + _matrix[8] * mat._matrix[7],
		_matrix[6] * mat._matrix[2] + _matrix[7] * mat._matrix[5] + _matrix[8] * mat._matrix[8]
	});
}

Vec3 Matrix3x3::operator*(const Vec3& vec) const
{
	return {
		_matrix[0] * vec.x + _matrix[1] * vec.y + _matrix[2] * vec.z,
		_matrix[3] * vec.x + _matrix[4] * vec.y + _matrix[5] * vec.z,
		_matrix[6] * vec.x + _matrix[7] * vec.y + _matrix[8] * vec.z
	};
}

Matrix3x3 Matrix3x3::rotate(double angleX, double angleY, double angleZ, MultiplicationOrder order)
{

	Matrix3x3 matZ = (int) (angleZ * EPSILON) != 0 ? rotateZ(angleZ) : identity();
	Matrix3x3 matY = (int) (angleY * EPSILON) != 0 ? rotateY(angleY) : identity();
	Matrix3x3 matX = (int) (angleX * EPSILON) != 0 ? rotateX(angleX) : identity();

	switch (order)
	{
	case XYZ: return matZ * matY * matX;
	case XZY: return matY * matZ * matX;
	case YZX: return matX * matZ * matY;
	case YXZ: return matZ * matX * matY;
	case ZXY: return matY * matX * matZ;
	case ZYX: return matX * matY * matZ;
	default: return identity();
	}
}