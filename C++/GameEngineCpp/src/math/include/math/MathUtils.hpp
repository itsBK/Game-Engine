#pragma once

namespace GameEngine::Math {

constexpr double EPSILON = 1e-9;

constexpr double clamp(double value, double minVal, double maxVal);

constexpr bool isZero(double value);
constexpr bool isZero(double value, double epsilon);

}
