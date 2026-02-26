cmake_minimum_required(VERSION 3.10.0)
project(FirstOpenGLProject VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)


find_package(OpenGL REQUIRED)

add_executable(FirstOpenGLProject 
    src/main.cpp 
    src/glad.h 
    src/glad.c 
    src/VAO.cpp 
    src/VBO.cpp 
    src/EBO.cpp 
    src/shaderClass.cpp 
)

target_link_libraries(FirstOpenGLProject 
    glfw 
    OpenGL::GL
    )

# this was done with AI cause stuff wouldnt work without this
target_include_directories(FirstOpenGLProject PRIVATE
    ${CMAKE_SOURCE_DIR}/Headers
    ${CMAKE_SOURCE_DIR}/src
)
# Also made with AI

# Copy Resources/ into the runtime directory next to the executable so
# the program can open "Resources/default.vert" using a relative path even
# when the working directory differs (e.g. VS Code launch presets).
add_custom_command(TARGET FirstOpenGLProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Resources
            $<TARGET_FILE_DIR:FirstOpenGLProject>/Resources
)