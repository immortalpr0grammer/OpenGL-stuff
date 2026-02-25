#include <VBO.hpp>
// The constructor
VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
    // Generating the buffer, binding it and giving it the vertices as data
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
// Method to bind it
void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}
// Method to unbind it
void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
// Method to delete it
void VBO::Delete() {
    glDeleteBuffers(1, &ID);
}