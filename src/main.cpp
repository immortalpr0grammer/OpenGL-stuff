#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>

// The raw source code for the shaders
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";



int main() {

    GLFWwindow* window;

    // Checking if glfw succeeded to initialize
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // Creating an array with vertices of each point. In order XYZ
    GLfloat vertices[] = {
        1.0f, 1.0f, 0,
        1.0f, -1.0f, 0,
        -1.0f, -1.0f, 0
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

    // Creating the shaders, connecting them to the source code and compiling them so the GPU understands it
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Creating the shader program, attaching the shaders to it and then link the program to the final executable
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Deleting the shaders, since we already put them in the program, so we dont need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Creating the Vertex Buffer (batch of data) Object and the Vertex Array Object
    GLuint VAO, VBO;

    // The first parameter is the amount of objects to render
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Binding them, so that when we do a function for them it knows we want to use that specific one
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Connecting the vertices to it, so that we now have a nicely packed buffer with all the data OpenGL needs
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Enabling the VAO or something like that, idk this is hard
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Unbinding the VAO and the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Specifying the color to use when clearing the buffers
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Getting any events
        glfwPollEvents();
        // Getting the current window size
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        // Giving OpenGL the window size to make it scale properly
        glViewport(0,0, width, height);


        // Setting the current backbuffer color to the specified glClear color
        glClear(GL_COLOR_BUFFER_BIT);
        // Making sure we actually use the shit we made
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        // Drawing the triangle. The 3 stands for the amount of vertices btw
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swapping the two buffers around
        glfwSwapBuffers(window);
    }
    
    // Deleting the shit we made
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);


    // Terminating the glfw library and everything created with it
    glfwTerminate();
    return 0;
}