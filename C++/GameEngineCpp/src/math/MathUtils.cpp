#include "include/math/MathUtils.hpp"

using namespace GameEngine::Math;


constexpr double clamp(double value, double minVal, double maxVal) {
    return value < minVal ? minVal : (value > maxVal ? maxVal : value);
}

constexpr bool isZero(double value) {
    return isZero(value, EPSILON);
}

constexpr bool isZero(double value, double epsilon) {
    return value > -epsilon && value < epsilon;
}

constexpr double clampAngle(double angle)
{
    while (angle < -PI) angle += 2 * PI;
    while (angle > PI) angle -= 2 * PI;
    return angle;
}
