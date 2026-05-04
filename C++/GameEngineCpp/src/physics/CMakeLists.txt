project(GameEngine.Physics)

add_library(${PROJECT_NAME} SHARED
    Circle.cpp
    Rect.cpp
    OrientedRect.cpp
    Sphere.cpp
    AABB.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PRIVATE GameEngine.Math)
