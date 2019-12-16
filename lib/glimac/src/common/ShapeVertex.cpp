#include "glimac/common/ShapeVertex.hpp"

namespace glimac {

    ShapeVertex& ShapeVertex::operator=(const ShapeVertex &src) {
        if(this != &src) {
            position = src.position;
            normal = src.normal;
            texCoords = src.texCoords;
        }
        return *this;
    }

    ShapeVertex& ShapeVertex::operator=(const ShapeVertexHomo &src) {
        position = glm::vec3(src.position);
        normal = glm::vec3(src.normal);
        texCoords = src.texCoords;
        return *this;
    }

}