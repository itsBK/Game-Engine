project(glfw VERSION 3.4)
add_library(${PROJECT_NAME} IMPORTED SHARED GLOBAL)
target_include_directories(${PROJECT_NAME} INTERFACE include)

set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libglfw.so.3.4
)
