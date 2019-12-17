#include "glimac/common/Object.hpp"

namespace glimac {

Object::Object(const GLsizei &nbVertex, const GLsizei &nbIndex, const ShapeVertex* vertices, const uint32_t* indexes) {

    glGenBuffers(1, &m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, nbVertex * sizeof(ShapeVertex), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glGenBuffers(1, &m_ibo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbIndex * sizeof(uint32_t), indexes, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

const GLuint Object::vbo() const {
    return m_vbo;
}

const GLuint Object::ibo() const {
    return m_ibo;
}

}