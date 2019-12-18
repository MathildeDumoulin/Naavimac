#ifndef SHAPEVERTEX_HPP__
#define SHAPEVERTEX_HPP__
#pragma once

#include <GL/glew.h>
#include "glimac/common/glm.hpp"
#include <vector>

namespace glimac {


struct ShapeVertexHomo {
    glm::vec4 position = glm::vec4(0.f, 0.f, 0.f, 1.f);
    glm::vec4 normal = glm::vec4(0.f, 0.f, 0.f, 0.f);
    glm::vec2 texCoords = glm::vec2(0.f, 0.f);

    ShapeVertexHomo() = default;
    ShapeVertexHomo(glm::vec4 pos, glm::vec4 norm, glm::vec2 tex) : position(pos), normal(norm), texCoords(tex) {}

    void transform(const glm::mat4 &mat);
};

struct ShapeVertex {
    glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 normal = glm::vec3(0.f, 0.f, 0.f);
    glm::vec2 texCoords = glm::vec2(0.f, 0.f);

    ShapeVertex() = default;
    ShapeVertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex) : position(pos), normal(norm), texCoords(tex) {}
    ShapeVertex(const ShapeVertex &src) : ShapeVertex(src.position, src.normal, src.texCoords) {} 
    ShapeVertex(const ShapeVertexHomo &src) : ShapeVertex(glm::vec3(src.position), glm::vec3(src.normal), src.texCoords) {} 

    ShapeVertex& operator=(const ShapeVertex &src);
    ShapeVertex& operator=(const ShapeVertexHomo &src);
};


void transformShapeVertexVector(std::vector<ShapeVertexHomo> &vec, const glm::mat4 &mat);


}

#endif
