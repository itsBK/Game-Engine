project(glad VERSION 4.0)
add_library(${PROJECT_NAME} SHARED src/glad.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
