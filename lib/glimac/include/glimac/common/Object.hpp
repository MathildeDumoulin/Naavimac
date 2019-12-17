#ifndef OBJECT_HPP__
#define OBJECT_HPP__
#pragma once

#include <GL/glew.h>
#include "glimac/common/ShapeVertex.hpp"

namespace glimac {

class Object {
    private:
        GLuint m_vbo;
        GLuint m_ibo;

    public:
        Object(const GLsizei &nbVertex, const GLsizei &nbIndex, const ShapeVertex* vertices, const uint32_t* indexes);

        const GLuint vbo() const;
        const GLuint ibo() const;
};

}


#endif