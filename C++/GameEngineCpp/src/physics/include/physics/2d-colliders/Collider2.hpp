#pragma once

#include <variant>

#include "Circle.hpp"
#include "Rect.hpp"
#include "OrientedRect.hpp"

namespace GameEngine::Physics::Bounds {
using namespace GameEngine::Math;

using Collider2 = std::variant<Circle, Rect, OrientedRect>;

}
