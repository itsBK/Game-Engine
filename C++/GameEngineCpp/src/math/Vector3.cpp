#include "Vector3.h"

using namespace math;

Vector3::Vector3() {
    Vector3::x = 0;
    Vector3::y = 0;
    Vector3::z = 0;
}

Vector3::Vector3(double x, double y, double z) {
    Vector3::x = x;
    Vector3::y = y;
    Vector3::z = z;
}
Vector3::Vector3(const Vector3& other) {
    Vector3::x = other.x;
    Vector3::y = other.y;
    Vector3::z = other.z;
}

Vector3::~Vector3() {
}

Vector3 Vector3::operator=(const Vector3& other) {
    return Vector3(other.x, other.y, other.z);
}

Vector3 Vector3::operator+(const Vector3& other) {
    return Vector3(
        this->x + other.x,
        this->y + other.y,
        this->z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) {
    return Vector3(
        this->x - other.x,
        this->y - other.y,
        this->z - other.z);
}

Vector3 Vector3::operator+(const double scalar) {
    return Vector3(
        this->x + scalar,
        this->y + scalar,
        this->z + scalar
    );
}

Vector3 Vector3::operator-(const double scalar) {
    return Vector3(
        this->x - scalar,
        this->y - scalar,
        this->z - scalar
    );
}

Vector3 Vector3::operator*(const double scalar) {
    return Vector3(
        this->x * scalar,
        this->y * scalar,
        this->z * scalar
    );
}

Vector3 Vector3::operator/(const double scalar) {
    return Vector3(
        this->x / scalar,
        this->y / scalar,
        this->z / scalar
    );
}

Vector3& Vector3::operator+=(const Vector3& other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;

    return *this;
}

Vector3& Vector3::operator+=(const double scalar) {
    this->x += scalar;
    this->y += scalar;
    this->z += scalar;

    return *this;
}

Vector3& Vector3::operator-=(const double scalar) {
    this->x -= scalar;
    this->y -= scalar;
    this->z -= scalar;

    return *this;
}

Vector3& Vector3::operator*=(const double scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;

    return *this;
}

Vector3& Vector3::operator/=(const double scalar) {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;

    return *this;
}

Vector3 Vector3::copy() {
    return Vector3(x, y, z);
}

double Vector3::length() {
    return sqrt(x * x + y * y + z * z);
}

double Vector3::lengthSq() {
    return x * x + y * y + z * z;
}

Vector3* Vector3::normalize() {
    double len = this->length();
    if (len != 0) {
        this->x /= len;
        this->y /= len;
        this->z /= len;
    }
    return this;
}

Vector3 Vector3::normalized() {
    double len = this->length();
    if (len != 0) {
        return *this / len;
    }
    return Vector3(x, y, z);
}


/*Vector3* Vector3::rotate(double angle, double axisX, double axisY, double axisZ) {
    double inVec[4] = { x, y, z, 1 };
    double matrix[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    Matrix.rotateM(matrix, 0, angle, axisX, axisY, axisZ);
    Matrix.multiplyMV(outVec, 0, matrix, 0, inVec, 0);
    x = outVec[0];
    y = outVec[1];
    z = outVec[2];
    return this;
}
*/

double Vector3::distance(Vector3 other) {
    double distX = this->x - other.x;
    double distY = this->y - other.y;
    double distZ = this->y - other.z;
    return sqrt(distX * distX + distY * distY + distZ * distZ);
}

double Vector3::distanceSq(Vector3 other) {
    double distX = this->x - other.x;
    double distY = this->y - other.y;
    double distZ = this->z - other.z;
    return distX * distX + distY * distY + distZ * distZ;
}

double Vector3::distance(Vector3& a, Vector3& b) {
    double distX = a.x - b.x;
    double distY = a.y - b.y;
    double distZ = a.z - b.z;
    return sqrt(distX * distX + distY * distY + distZ * distZ);
}
 
double Vector3::distanceSq(Vector3& a, Vector3& b) {
    double distX = a.x - b.x;
    double distY = a.y - b.y;
    double distZ = a.z - b.z;
    return distX * distX + distY * distY + distZ * distZ;
}