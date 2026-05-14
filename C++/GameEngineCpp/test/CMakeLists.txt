cmake_minimum_required(VERSION 3.18)
project(GameEngineTest VERSION 0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME} openGL/1.FirstShader.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE GameEngine)
