#pragma once

#include "2d-colliders/Circle.hpp"
#include "2d-colliders/Rect.hpp"
#include "2d-colliders/OrientedRect.hpp"
#include "2d-colliders/Collider2.hpp"

#include "3d-colliders/Sphere.hpp"
#include "3d-colliders/AABB.hpp"
#include "3d-colliders/OBB.hpp"
#include "3d-colliders/Collider3.hpp"

namespace GameEngine::Physics {

class CollisionDetector
{
public:
    static bool check(const Bounds::Collider2& a, const Bounds::Collider2& b);
    static bool check(const Bounds::Collider3& a, const Bounds::Collider3& b);

private:
    struct Visitor2
    {
        inline bool operator()(const Bounds::Circle& a, const Bounds::Circle& b) const;
        inline bool operator()(const Bounds::Circle& a, const Bounds::Rect& b) const;
        inline bool operator()(const Bounds::Circle& a, const Bounds::OrientedRect& b) const;
        inline bool operator()(const Bounds::Rect& a, const Bounds::Rect& b) const;
        inline bool operator()(const Bounds::Rect& a, const Bounds::OrientedRect& b) const;
        inline bool operator()(const Bounds::OrientedRect& a, const Bounds::OrientedRect& b) const;

        inline bool operator()(const Bounds::Rect& a, const Bounds::Circle& b) const;
        inline bool operator()(const Bounds::OrientedRect& a, const Bounds::Circle& b) const;
        inline bool operator()(const Bounds::OrientedRect& a, const Bounds::Rect& b) const;
    };

    struct Visitor3
    {
        inline bool operator()(const Bounds::Sphere& a, const Bounds::Sphere& b) const;
        inline bool operator()(const Bounds::Sphere& a, const Bounds::AABB& b) const;
        inline bool operator()(const Bounds::Sphere& a, const Bounds::OBB& b) const;
        inline bool operator()(const Bounds::AABB& a, const Bounds::AABB& b) const;
        inline bool operator()(const Bounds::AABB& a, const Bounds::OBB& b) const;
        inline bool operator()(const Bounds::OBB& a, const Bounds::OBB& b) const;

        inline bool operator()(const Bounds::AABB& a, const Bounds::Sphere& b) const;
        inline bool operator()(const Bounds::OBB& a, const Bounds::Sphere& b) const;
        inline bool operator()(const Bounds::OBB& a, const Bounds::AABB& b) const;
    };

    static Visitor2 _visitor2;
    static Visitor3 _visitor3;
};

}
