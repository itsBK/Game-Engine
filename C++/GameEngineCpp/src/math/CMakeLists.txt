project(GameEngine.Math)

add_library(${PROJECT_NAME} SHARED
    Vec2.cpp
    Vec3.cpp
    Pose2.cpp
    Pose3.cpp
    Rot3.cpp
    Matrix3x3.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)
