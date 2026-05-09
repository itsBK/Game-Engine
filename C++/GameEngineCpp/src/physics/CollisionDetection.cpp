#include "include/physics/CollisionDetection.hpp"

#include <cmath>
#include <variant>
#include <math/MathUtils.hpp>

using namespace GameEngine::Physics;
using namespace GameEngine::Physics::Bounds;
using namespace GameEngine::Math;

bool CollisionDetector::check(const Collider2& a, const Collider2& b)
{
    static Visitor2 visitor2;
    return std::visit(visitor2, a, b);
}

bool CollisionDetector::check(const Collider3& a, const Collider3& b)
{
    static Visitor3 visitor3;
    return std::visit(visitor3, a, b);
}


inline bool CollisionDetector::Visitor2::operator()(const Circle& a, const Circle& b) const
{
    double r = a.radius + b.radius;
    return a.center.distSq(b.center) <= r * r;
}

inline bool CollisionDetector::Visitor2::operator()(const Circle& a, const Rect& b) const
{
    auto rMin = b.min();
    auto rMax = b.max();
    auto closest = Vec2::clamp(a.center, rMin, rMax);
    return closest.distSq(a.center) <= a.radius * a.radius;
}

inline bool CollisionDetector::Visitor2::operator()(const Circle& a, const OrientedRect& b) const
{
    Vec2 localCenter = b.transform.local(a.center);
    Vec2 closest = Vec2::clamp(localCenter, -0.5 * b.size, 0.5 * b.size);
    return closest.distSq(localCenter) <= a.radius * a.radius;
}

inline bool CollisionDetector::Visitor2::operator()(const Rect& a, const Rect& b) const
{
    auto aMin = a.min(), aMax = a.max();
    auto bMin = b.min(), bMax = b.max();
    return aMin.x <= bMax.x && bMin.x <= aMax.x &&
           aMin.y <= bMax.y && bMin.y <= aMax.y;
}

inline bool CollisionDetector::Visitor2::operator()(const Rect& a, const OrientedRect& b) const
{
    auto b_aabb = b.aabb();
    if (!(*this)(a, b_aabb))
        return false;

    std::array<Vec2, 4> axes {
        Vec2{ 1, 0 }, Vec2{ 0, 1 },
        b.transform.forward, b.transform.left()
    };

    const auto& aCorners = std::array<Vec2, 4>{
        a.min(), a.max(), Vec2{ a.min().x, a.max().y }, Vec2{ a.max().x, a.min().y }
    };
    const auto& bCorners = b.corners();

    for (const auto& axe : axes)
    {
        double a_min = INFINITY, a_max = -INFINITY;
        for (const auto& corner : aCorners)
        {
            auto cornerLoc = corner * axe;
            if (cornerLoc < a_min) a_min = cornerLoc;
            if (cornerLoc > a_max) a_max = cornerLoc;
        }

        double b_min = INFINITY, b_max = -INFINITY;
        for (const auto& corner : bCorners)
        {
            auto cornerLoc = corner * axe;
            if (cornerLoc < b_min) b_min = cornerLoc;
            if (cornerLoc > b_max) b_max = cornerLoc;
        }

        if (a_min > b_max || b_min > a_max)
            return false;
    }

    return true;
}

inline bool CollisionDetector::Visitor2::operator()(const OrientedRect& a, const OrientedRect& b) const
{
    if (!(*this)(a.aabb(), b.aabb()))
        return false;

    std::array<Vec2, 4> axes {
        a.transform.forward, a.transform.left(),
        b.transform.forward, b.transform.left()
    };

    const auto& aCorners = a.corners();
    const auto& bCorners = b.corners();

    for (const auto& axe : axes)
    {
        double a_min = INFINITY, a_max = -INFINITY;
        for (const auto& corner : aCorners)
        {
            auto cornerLoc = corner * axe;
            if (cornerLoc < a_min) a_min = cornerLoc;
            if (cornerLoc > a_max) a_max = cornerLoc;
        }

        double b_min = INFINITY, b_max = -INFINITY;
        for (const auto& corner : bCorners)
        {
            auto cornerLoc = corner * axe;
            if (cornerLoc < b_min) b_min = cornerLoc;
            if (cornerLoc > b_max) b_max = cornerLoc;
        }

        if (a_min > b_max || b_min > a_max)
            return false;
    }

    return true;
}

inline bool CollisionDetector::Visitor2::operator()(const Rect& a, const Circle& b) const
{
    return (*this)(b, a);
}

inline bool CollisionDetector::Visitor2::operator()(const OrientedRect& a, const Circle& b) const
{
    return (*this)(b, a);
}

inline bool CollisionDetector::Visitor2::operator()(const OrientedRect& a, const Rect& b) const
{
    return (*this)(b, a);
}







inline bool CollisionDetector::Visitor3::operator()(const Sphere& a, const Sphere& b) const
{
    double r = a.radius + b.radius;
    return a.center.distSq(b.center) <= r * r;
}

inline bool CollisionDetector::Visitor3::operator()(const Sphere& a, const AABB& b) const
{
    auto bMin = b.min();
    auto bMax = b.max();
    auto closest = Vec3::clamp(a.center, bMin, bMax);
    return closest.distSq(a.center) <= a.radius * a.radius;
}

inline bool CollisionDetector::Visitor3::operator()(const Sphere& a, const OBB& b) const
{
    Vec3 localCenter = b.transform.local(a.center);
    auto closest = Vec3::clamp(localCenter, -0.5 * b.size, 0.5 * b.size);
    return closest.distSq(localCenter) <= a.radius * a.radius;
}

inline bool CollisionDetector::Visitor3::operator()(const AABB& a, const AABB& b) const
{
    auto aMin = a.min(), aMax = a.max();
    auto bMin = b.min(), bMax = b.max();
    return aMin.x <= bMax.x && bMin.x <= aMax.x &&
           aMin.y <= bMax.y && bMin.y <= aMax.y &&
           aMin.z <= bMax.z && bMin.z <= aMax.z;
}

inline bool CollisionDetector::Visitor3::operator()(const AABB& a, const OBB& b) const
{
    //TODO
    return false;
}

inline bool CollisionDetector::Visitor3::operator()(const OBB& a, const OBB& b) const
{
    //TODO
    return false;
}

inline bool CollisionDetector::Visitor3::operator()(const AABB& a, const Sphere& b) const
{
    return (*this)(b, a);
}

inline bool CollisionDetector::Visitor3::operator()(const OBB& a, const Sphere& b) const
{
    return (*this)(b, a);
}

inline bool CollisionDetector::Visitor3::operator()(const OBB& a, const AABB& b) const
{
    return (*this)(b, a);
}
