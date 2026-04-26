#pragma once

namespace GameEngine::Math {

constexpr double EPSILON = 1e-12;
constexpr double PI = 3.14159265358979323846;

constexpr double clamp(double value, double minVal, double maxVal);

constexpr bool isZero(double value);
constexpr bool isZero(double value, double epsilon);
/// @return angle in range [-pi, pi]
constexpr double clampAngle(double angle);

}
