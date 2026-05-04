#pragma once

#include <variant>

#include "Sphere.hpp"
#include "AABB.hpp"
#include "OBB.hpp"

namespace GameEngine::Physics::Bounds {
using namespace GameEngine::Math;

using Collider3 = std::variant<Sphere, AABB, OBB>;

}
