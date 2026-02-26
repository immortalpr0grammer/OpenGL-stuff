#pragma once

#include "glad.h"
#include <VBO.hpp>

class VAO {

    public:
        GLuint ID;
        VAO();
        // For linking the shaders
        void LinkAttrib(VBO VBO, GLuint layout, GLuint numcomponents, GLenum type, GLsizeiptr stride, void* offset);
        void Bind();
        void Unbind();
        void Delete();

};