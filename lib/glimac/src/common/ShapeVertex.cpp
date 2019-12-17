#include "glimac/common/ShapeVertex.hpp"

namespace glimac {

void ShapeVertexHomo::transform(const glm::mat4 &mat) {
    position = mat * position;
    normal = mat * normal;
}


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



void transformShapeVertexVector(std::vector<ShapeVertexHomo> &vec, const glm::mat4 &mat) {
    for(auto &v:vec) {
        v.transform(mat);
    }
}

}