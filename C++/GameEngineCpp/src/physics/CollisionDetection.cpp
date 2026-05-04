#include "include/physics/CollisionDetection.hpp"

#include <algorithm>
#include <variant>

using namespace GameEngine::Physics;
using namespace GameEngine::Math;

bool CollisionDetector::check(const Bounds::Collider2& a, const Bounds::Collider2& b)
{
    static Visitor2 visitor2;
    return std::visit(visitor2, a, b);
}

bool CollisionDetector::check(const Bounds::Collider3& a, const Bounds::Collider3& b)
{
    static Visitor3 visitor3;
    return std::visit(visitor3, a, b);
}


inline bool CollisionDetector::Visitor2::operator()(const Bounds::Circle& a, const Bounds::Circle& b) const
{
    double r = a.radius + b.radius;
    return a.center.distSq(b.center) <= r * r;
}

inline bool CollisionDetector::Visitor2::operator()(const Bounds::Circle& a, const Bounds::Rect& b) const
{
    auto rMin = b.min();
    auto rMax = b.max();
    Vec2 closest = {
        std::clamp(a.center.x, rMin.x, rMax.x),
        std::clamp(a.center.y, rMin.y, rMax.y)
    };
    return closest.distSq(a.center) <= a.radius * a.radius;
}

inline bool CollisionDetector::Visitor2::operator()(const Bounds::Circle& a, const Bounds::OrientedRect& b) const
{
    Vec2 localCenter = b.transform.local(a.center);

    Vec2 closest = {
        std::clamp(localCenter.x, -b.size.x * 0.5, b.size.x * 0.5),
        std::clamp(localCenter.y, -b.size.y * 0.5, b.size.y * 0.5)
    };
    return closest.distSq(localCenter) <= a.radius * a.radius;
}

inline bool CollisionDetector::Visitor2::operator()(const Bounds::Rect& a, const Bounds::Rect& b) const
{
    auto aMin = a.min(), aMax = a.max();
    auto bMin = b.min(), bMax = b.max();
    return aMin.x <= bMax.x && bMin.x <= aMax.x &&
           aMin.y <= bMax.y && bMin.y <= aMax.y;
}

inline bool CollisionDetector::Visitor2::operator()(const Bounds::Rect& a, const Bounds::OrientedRect& b) const
{
    //TODO
    return false;
}

inline bool CollisionDetector::Visitor2::operator()(const Bounds::OrientedRect& a, const Bounds::OrientedRect& b) const
{
    //TODO
    return false;
}

inline bool CollisionDetector::Visitor2::operator()(const Bounds::Rect& a, const Bounds::Circle& b) const
{
    return (*this)(b, a);
}

inline bool CollisionDetector::Visitor2::operator()(const Bounds::OrientedRect& a, const Bounds::Circle& b) const
{
    return (*this)(b, a);
}

inline bool CollisionDetector::Visitor2::operator()(const Bounds::OrientedRect& a, const Bounds::Rect& b) const
{
    return (*this)(b, a);
}







inline bool CollisionDetector::Visitor3::operator()(const Bounds::Sphere& a, const Bounds::Sphere& b) const
{
    double r = a.radius + b.radius;
    return a.center.distSq(b.center) <= r * r;
}

inline bool CollisionDetector::Visitor3::operator()(const Bounds::Sphere& a, const Bounds::AABB& b) const
{
    auto bMin = b.min();
    auto bMax = b.max();
    Vec3 closest = {
        std::clamp(a.center.x, bMin.x, bMax.x),
        std::clamp(a.center.y, bMin.y, bMax.y),
        std::clamp(a.center.z, bMin.z, bMax.z)
    };
    return closest.distSq(a.center) <= a.radius * a.radius;
}

inline bool CollisionDetector::Visitor3::operator()(const Bounds::Sphere& a, const Bounds::OBB& b) const
{
    Vec3 localCenter = b.transform.local(a.center);
    Vec3 closest = {
        std::clamp(localCenter.x, -b.size.x * 0.5, b.size.x * 0.5),
        std::clamp(localCenter.y, -b.size.y * 0.5, b.size.y * 0.5),
        std::clamp(localCenter.z, -b.size.z * 0.5, b.size.z * 0.5)
    };
    return closest.distSq(localCenter) <= a.radius * a.radius;
}

inline bool CollisionDetector::Visitor3::operator()(const Bounds::AABB& a, const Bounds::AABB& b) const
{
    auto aMin = a.min(), aMax = a.max();
    auto bMin = b.min(), bMax = b.max();
    return aMin.x <= bMax.x && bMin.x <= aMax.x &&
           aMin.y <= bMax.y && bMin.y <= aMax.y &&
           aMin.z <= bMax.z && bMin.z <= aMax.z;
}

inline bool CollisionDetector::Visitor3::operator()(const Bounds::AABB& a, const Bounds::OBB& b) const
{
    //TODO
    return false;
}

inline bool CollisionDetector::Visitor3::operator()(const Bounds::OBB& a, const Bounds::OBB& b) const
{
    //TODO
    return false;
}

inline bool CollisionDetector::Visitor3::operator()(const Bounds::AABB& a, const Bounds::Sphere& b) const
{
    return (*this)(b, a);
}

inline bool CollisionDetector::Visitor3::operator()(const Bounds::OBB& a, const Bounds::Sphere& b) const
{
    return (*this)(b, a);
}

inline bool CollisionDetector::Visitor3::operator()(const Bounds::OBB& a, const Bounds::AABB& b) const
{
    return (*this)(b, a);
}
