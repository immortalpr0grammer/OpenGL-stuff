#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>

#include "shaderClass.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"


int main() {

    GLFWwindow* window;

    // Checking if glfw succeeded to initialize
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // Creating an array with vertices of each point. In order XYZ
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, // Bottom left corner
        -0.5f, 0.0f, 0.0f, // Centered height and towards the left
        0.0f, -1.0f, 0.0f, // Bottom middle
        1.0f, -1.0f, 0.0f, // Bottom right corner
        0.5f, 0.0f, 0.0f, // Centered height and towards the right
        0.0f, 1.0f, 0.0f // Top middle
    };
    // Creating an array with the data for which points from the vertices array to use for the triangles
    GLuint indices[] = {
        0, 1, 2, // Lower left triangle
        3, 4, 2, // Lower right triangle
        1, 4, 5 // Top middle triangle
    };


    // Creating the window and making it the current context
    window = glfwCreateWindow(640, 480, "Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Checking if OpenGL succeeded to load
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to load OpenGL!" << std::endl;
        glfwTerminate();
        return -1;
    }

    Shader shaderprogram("Resources/default.vert", "Resources/default.frag");
    
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Specifying the color to use when clearing the buffers
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Getting any events
        glfwPollEvents();
        // Getting the current window size
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        // Telling OpenGL the window size to make it scale properly
        glViewport(0,0, width, height);

        // Setting the current backbuffer color to the specified glClear color
        glClear(GL_COLOR_BUFFER_BIT);
        // Making sure we actually use the shit we made
        shaderprogram.Activate();
        VAO1.Bind();
        // Drawing the triangles. The 9 stands for the amount of vertices btw
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        // Swapping the two buffers around
        glfwSwapBuffers(window);
    }
    
    // Deleting the shit we made
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderprogram.Delete();

    // Terminating the glfw library and everything created with it
    glfwTerminate();
    return 0;
}