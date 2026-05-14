cmake_minimum_required(VERSION 3.18)
project(GameEngine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(3rdParty)
add_subdirectory(src)

add_library(${PROJECT_NAME} SHARED
    src/core/Application.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC src/core/include)
target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC GameEngine.Math GameEngine.Physics)

add_subdirectory(test)
