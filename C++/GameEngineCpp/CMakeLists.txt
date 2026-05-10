cmake_minimum_required (VERSION 3.18)
project(GameEngine
    VERSION 0.1
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_executable (${PROJECT_NAME} GameEngine.cpp)

add_subdirectory(src)
# target_link_libraries(${PROJECT_NAME} PUBLIC GameEngine.Math GameEngine.Physics)
