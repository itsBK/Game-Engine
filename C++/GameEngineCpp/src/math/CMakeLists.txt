project(GameEngine.Math)

add_library(${PROJECT_NAME} SHARED
    Vec2.cpp
    Vec3.cpp
    Pose2.cpp
    Transform2.cpp
    Matrix3x3.cpp
    MathUtils.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)
