cmake_minimum_required (VERSION 3.18)
set(GameEngineProject GameEngine)
project(${GameEngineProject}
    VERSION 0.1
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    message("using MSVC")
    add_executable (${PROJECT_NAME}
        src/os/windows/GameEngine.cpp)

elseif (UNIX)
    message("using GNU")
    add_executable (${PROJECT_NAME}
        src/os/linux/GameEngine.cpp)

endif ()

target_include_directories(${PROJECT_NAME} PUBLIC src/os/include)

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PUBLIC GameEngine.Math)
