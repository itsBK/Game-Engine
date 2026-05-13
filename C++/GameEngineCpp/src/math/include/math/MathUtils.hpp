#pragma once

namespace GameEngine::Math {

constexpr double EPSILON = 1e-12;
constexpr double PI = 3.14159265358979323846;

constexpr double clamp(double value, double minVal, double maxVal) {
    return value < minVal ? minVal : (value > maxVal ? maxVal : value);
}

constexpr bool isZero(double value, double epsilon = EPSILON) {
    return value > -epsilon && value < epsilon;
}

/// @return angle in range [-pi, pi]
constexpr double clampAngle(double angle) {
    while (angle < -PI) angle += 2 * PI;
    while (angle > PI) angle -= 2 * PI;
    return angle;
}

}
