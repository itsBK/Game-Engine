#include "include/math/MathUtils.hpp"

using namespace GameEngine::Math;


constexpr double GameEngine::Math::clamp(double value, double minVal, double maxVal) {
    return value < minVal ? minVal : (value > maxVal ? maxVal : value);
}

constexpr bool GameEngine::Math::isZero(double value) {
    return isZero(value, EPSILON);
}

constexpr bool GameEngine::Math::isZero(double value, double epsilon) {
    return value > -epsilon && value < epsilon;
}

constexpr double GameEngine::Math::clampAngle(double angle)
{
    while (angle < -PI) angle += 2 * PI;
    while (angle > PI) angle -= 2 * PI;
    return angle;
}
