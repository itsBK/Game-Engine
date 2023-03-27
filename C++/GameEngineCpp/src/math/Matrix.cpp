#include "Matrix.h"

using namespace GameEngine::Math;

Matrix3x3::Matrix3x3() :
	m_matrix{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
{
}

Matrix3x3::Matrix3x3(double matrix[]) : m_matrix {
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

Matrix3x3 Matrix3x3::RotateX(double radians) {
	double _cos = cos(radians);
	double _sin = sin(radians);
	return Matrix3x3(new double[9] {
		1,    0,     0,
		0, _cos, -_sin,
		0, _sin,  _cos
	});
}

Matrix3x3 Matrix3x3::RotateY(const double radians) {
	double _cos = cos(radians);
	double _sin = sin(radians);
	return Matrix3x3(new double[9] {
		 _cos,  0, _sin,
		    0,  1,    0,
		-_sin,  0, _cos
	});
}

Matrix3x3 Matrix3x3::RotateZ(const double radians) {
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
		m_matrix[0] * mat.m_matrix[0] + m_matrix[1] * mat.m_matrix[3] + m_matrix[2] * mat.m_matrix[6],
		m_matrix[0] * mat.m_matrix[1] + m_matrix[1] * mat.m_matrix[4] + m_matrix[2] * mat.m_matrix[7],
		m_matrix[0] * mat.m_matrix[2] + m_matrix[1] * mat.m_matrix[5] + m_matrix[2] * mat.m_matrix[8],

		m_matrix[3] * mat.m_matrix[0] + m_matrix[4] * mat.m_matrix[3] + m_matrix[5] * mat.m_matrix[6],
		m_matrix[3] * mat.m_matrix[1] + m_matrix[4] * mat.m_matrix[4] + m_matrix[5] * mat.m_matrix[7],
		m_matrix[3] * mat.m_matrix[2] + m_matrix[4] * mat.m_matrix[5] + m_matrix[5] * mat.m_matrix[8],

		m_matrix[6] * mat.m_matrix[0] + m_matrix[7] * mat.m_matrix[3] + m_matrix[8] * mat.m_matrix[6],
		m_matrix[6] * mat.m_matrix[1] + m_matrix[7] * mat.m_matrix[4] + m_matrix[8] * mat.m_matrix[7],
		m_matrix[6] * mat.m_matrix[2] + m_matrix[7] * mat.m_matrix[5] + m_matrix[8] * mat.m_matrix[8],
	});
}

Vector3 Matrix3x3::operator*(const Vector3& vec) {
	return Vector3(
		m_matrix[0] * vec.x + m_matrix[1] * vec.y + m_matrix[2] * vec.z,
		m_matrix[3] * vec.x + m_matrix[4] * vec.y + m_matrix[5] * vec.z,
		m_matrix[6] * vec.x + m_matrix[7] * vec.y + m_matrix[8] * vec.z
	);
}

Matrix3x3 Matrix3x3::Rotate(double angleX, double angleY, double angleZ,
	MultiplicationOrder order) {

	Matrix3x3 matZ = (int) (angleZ * AFTER_COMMA_PRECISION) != 0 ?
					Matrix3x3::RotateZ(angleZ) :
					Matrix3x3::identity();
	Matrix3x3 matY = (int) (angleY * AFTER_COMMA_PRECISION) != 0 ?
					Matrix3x3::RotateY(angleY) :
					Matrix3x3::identity();
	Matrix3x3 matX = (int) (angleX * AFTER_COMMA_PRECISION) != 0 ?
					Matrix3x3::RotateX(angleX) :
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