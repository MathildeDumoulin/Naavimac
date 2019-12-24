#ifndef VERTEX_ARRAY_HPP__
#define VERTEX_ARRAY_HPP__
#pragma once

#include <GL/glew.h>
#include "glimac/common/Object.hpp"

namespace glimac {

enum ShaderAttrib {
    POS = 0, POS_NORM = 1, POS_NORM_TEXT = 2
};

class VertexArray {
    private:
        GLuint m_vao;

    public:
        VertexArray(const ShaderAttrib& attrib, const Object& obj);
        ~VertexArray();

        const GLuint vao() const;
        void bindVAO() const;
        void unbindVAO() const;
};

}

#endif