#include "Matrix.h"

using namespace GameEngine::Math;

Matrix3x3::Matrix3x3() :
	_matrix{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
{
}

Matrix3x3::Matrix3x3(double matrix[]) : _matrix {
		matrix[0], matrix[1], matrix[2],
		matrix[3], matrix[4], matrix[5],
		matrix[6], matrix[7], matrix[8]
	}
{
}

Matrix3x3 Matrix3x3::identity() {
	return Matrix3x3(new double[9] {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	});
}

Matrix3x3 Matrix3x3::rotateX(double radians) {
	double _cos = cos(radians);
	double _sin = sin(radians);
	return Matrix3x3(new double[9] {
		1,    0,     0,
		0, _cos, -_sin,
		0, _sin,  _cos
	});
}

Matrix3x3 Matrix3x3::rotateY(const double radians) {
	double _cos = cos(radians);
	double _sin = sin(radians);
	return Matrix3x3(new double[9] {
		 _cos,  0, _sin,
		    0,  1,    0,
		-_sin,  0, _cos
	});
}

Matrix3x3 Matrix3x3::rotateZ(const double radians) {
	double _cos = cos(radians);
	double _sin = sin(radians);
	return Matrix3x3(new double[9] {
		_cos, -_sin, 0,
		_sin,  _cos, 0,
		   0,     0, 1
	});
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& mat) {
	return Matrix3x3(new double[9] {
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

Vector3 Matrix3x3::operator*(const Vector3& vec) {
	return Vector3(
		_matrix[0] * vec.x + _matrix[1] * vec.y + _matrix[2] * vec.z,
		_matrix[3] * vec.x + _matrix[4] * vec.y + _matrix[5] * vec.z,
		_matrix[6] * vec.x + _matrix[7] * vec.y + _matrix[8] * vec.z
	);
}

Matrix3x3 Matrix3x3::rotate(double angleX, double angleY, double angleZ,
	MultiplicationOrder order) {

	Matrix3x3 matZ = (int) (angleZ * AFTER_COMMA_PRECISION) != 0 ?
					Matrix3x3::rotateZ(angleZ) :
					Matrix3x3::identity();
	Matrix3x3 matY = (int) (angleY * AFTER_COMMA_PRECISION) != 0 ?
					Matrix3x3::rotateY(angleY) :
					Matrix3x3::identity();
	Matrix3x3 matX = (int) (angleX * AFTER_COMMA_PRECISION) != 0 ?
					Matrix3x3::rotateX(angleX) :
					Matrix3x3::identity();

	Matrix3x3 result;
	switch (order)
	{
	case GameEngine::Math::Matrix3x3::XYZ:
		result = matZ * matY * matX;
		break;
	case GameEngine::Math::Matrix3x3::XZY:
		result = matY * matZ * matX;
		break;
	case GameEngine::Math::Matrix3x3::YZX:
		result = matX * matZ * matY;
		break;
	case GameEngine::Math::Matrix3x3::YXZ:
		result = matZ * matX * matY;
		break;
	case GameEngine::Math::Matrix3x3::ZXY:
		result = matY * matX * matZ;
		break;
	case GameEngine::Math::Matrix3x3::ZYX:
		result = matX * matY * matZ;
		break;
	default:
		break;
	}

	return result;
}