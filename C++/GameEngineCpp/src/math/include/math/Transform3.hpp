#pragma once

#include "Vec3.hpp"

namespace GameEngine::Math {

class Transform3
{

public:
    Vec3 pos = {};
    /// unit vector
    Vec3 forward = {1,0,0};
    /// unit vector
    Vec3 left = {0,1,0};

    Transform3() = default;
    Transform3(const Transform3& other) = default;
    Transform3& operator=(const Transform3& other) = default;
    ~Transform3() = default;

    Transform3(const Vec3& pos, const Vec3& forward, const Vec3& left);

    bool operator!=(const Transform3& other) const;
    bool operator==(const Transform3& other) const;

    inline double dist(const Vec3& other) const;
    inline double distSq(const Vec3& other) const;
    inline double dist(const Transform3& other) const;
    inline double distSq(const Transform3& other) const;

    /// @return local to global transformation
    Vec3 local(const Vec3& target) const;
    /// @return global to local transformation
    Vec3 global(const Vec3& target) const;
    /// @return local to global transformation
    Transform3 local(const Transform3& target) const;
    /// @return global to local transformation
    Transform3 global(const Transform3& target) const;

    inline Vec3 up() const;

    inline Vec3 mirrorVec(const Vec3& target) const;
    inline Vec3 mirrorPoint(const Vec3& target) const;
    Transform3 mirror(const Transform3& target) const;

private:
    inline Vec3 rotateForward(const Vec3& target) const;
    inline Vec3 rotateBackward(const Vec3& target) const;
};

}