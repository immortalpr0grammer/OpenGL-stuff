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
                            /*      Colors      */
        -1.0f, -1.0f, 0.0f,   1.0, 0.6, 0.11, // Bottom left corner
        -0.5f, 0.0f, 0.0f,    1.0, 0.6, 0.11, // Centered height and towards the left
        0.0f, -1.0f, 0.0f,    1.0, 0.6, 0.11, // Bottom middle
        1.0f, -1.0f, 0.0f,    1.0, 0.6, 0.11, // Bottom right corner
        0.5f, 0.0f, 0.0f,     1.0, 0.6, 0.11, // Centered height and towards the right
        0.0f, 1.0f, 0.0f,     1.0, 0.6, 0.11  // Top middle
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
    // Linking the vertices position data
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    // Linking the vertices color data
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // Unbinding everything
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderprogram.ID, "scale");

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
        // The second parameter is the scale of everything on the screen
        glUniform1f(uniID, 1);

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