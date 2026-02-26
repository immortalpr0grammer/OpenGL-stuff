#include <VAO.hpp>

// The constructor
VAO::VAO() {
    glGenVertexArrays(1, &ID);
}
// Linking the VBO to the VAO
void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numcomponents, GLenum type, GLsizeiptr stride, void* offset) {
    VBO.Bind();
    glVertexAttribPointer(layout, numcomponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind() {
    glBindVertexArray(ID);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::Delete() {
    glDeleteVertexArrays(1, &ID);
}