#include "glimac/common/Object.hpp"

namespace glimac {

Object::Object(const GLsizei &nbVertex, const GLsizei &nbIndex, const ShapeVertex* vertices, const uint32_t* indexes) 
    : m_vbo(0), m_ibo(0), m_nbVertex(nbVertex), m_nbIndex(nbIndex) {

        //Avoid memory leak
        if(glIsBuffer(m_vbo) == GL_TRUE) glDeleteBuffers(1, &m_vbo);
        if(glIsBuffer(m_ibo) == GL_TRUE) glDeleteBuffers(1, &m_ibo);

        //VBO Creation
        glGenBuffers(1, &m_vbo);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, nbVertex * sizeof(ShapeVertex), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //IBO Creation
        glGenBuffers(1, &m_ibo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbIndex * sizeof(uint32_t), indexes, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Object::Object(const Cube& cube) : Object(cube.nbVertex(), cube.nbIndex(), cube.verticesPointer(), cube.indexesPointer()) {}

Object::Object(const CubeEdges& cubeEdges) : Object(cubeEdges.nbVertex(), cubeEdges.nbIndex(), cubeEdges.verticesPointer(), cubeEdges.indexesPointer()) {}

Object::~Object() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
}


const GLuint Object::vbo() const {
    return m_vbo;
}

const GLuint Object::ibo() const {
    return m_ibo;
}

const GLsizei Object::nbVertex() const {
    return m_nbVertex;
}

const GLsizei Object::nbIndex() const {
    return m_nbIndex;
}

}