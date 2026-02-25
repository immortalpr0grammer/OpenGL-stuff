#include <EBO.hpp>

EBO::EBO(GLuint* indices, GLsizeiptr size) {
    // Generating the buffer, binding it and giving it the indices as data
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}
// Method to bind it
void EBO::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
// Method to unbind it
void EBO::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
// Method to delete it
void EBO::Delete() {
    glDeleteBuffers(1, &ID);
}