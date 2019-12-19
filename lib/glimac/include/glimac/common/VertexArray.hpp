#ifndef VERTEX_ARRAY_HPP__
#define VERTEX_ARRAY_HPP__
#pragma once

#include <GL/glew.h>
#include "glimac/common/Object.hpp"

namespace glimac {

class VertexArray {
    private:
        GLuint m_vao;

    public:
        VertexArray();
        void addObject(const Object &obj);

        const GLuint vao() const;
};

}

#endif