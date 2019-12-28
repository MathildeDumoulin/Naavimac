#ifndef OBJECT_HPP__
#define OBJECT_HPP__
#pragma once

#include <GL/glew.h>
#include "glimac/common/ShapeVertex.hpp"
#include "glimac/primitives/Cube.hpp"
#include "glimac/primitives/CubeEdges.hpp"
#include "glimac/common/Scene.hpp"
#include "glimac/shading/ShadingProgram.hpp"

namespace glimac {

class Object {
    private:
        GLuint m_vbo;
        GLuint m_ibo;
        GLsizei m_nbVertex;
        GLsizei m_nbIndex;

    public:
        Object(const GLsizei &nbVertex, const GLsizei &nbIndex, const ShapeVertex* vertices, const uint32_t* indexes);
        Object(const Cube& cube);
        Object(const CubeEdges& cubeEdges);
        ~Object();

        const GLuint vbo() const;
        const GLuint ibo() const;
        const GLsizei nbVertex() const;
        const GLsizei nbIndex() const;
};

}


#endif