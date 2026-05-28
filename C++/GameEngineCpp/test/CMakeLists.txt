cmake_minimum_required(VERSION 3.18)
project(GameEngineTest VERSION 0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME} CoreTest.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE GameEngine)

add_executable(1.FirstShader openGL/1.FirstShader.cpp)
target_link_libraries(1.FirstShader PRIVATE GameEngine)

add_executable(loggerMultipleRuns utilities/LogTest100Run.cpp)
target_link_libraries(loggerMultipleRuns PRIVATE GameEngine)

add_executable(loggerStressTest utilities/LogTest4MillionLogs.cpp)
target_link_libraries(loggerStressTest PRIVATE GameEngine)
