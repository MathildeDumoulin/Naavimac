#pragma once 

#include <vector>

#include "glimac/common/common.hpp"

namespace glimac {

class Cube {
    public:
        Cube();

        const ShapeVertex* getDataPointer() const;
        GLsizei getVertexCount() const;

    private:
        std::vector<ShapeVertex> m_Vertices;
        GLsizei m_nVertexCount;
};


const std::vector<ShapeVertexHomo> createSquareFace(const float &size);
void transformShapeVertex(ShapeVertexHomo &pt, const glm::mat4 &mat);
void transformShapeVertexVector(std::vector<ShapeVertexHomo> &vec, const glm::mat4 &mat);
void pushQuadIntoVector(std::vector<ShapeVertexHomo> &quad, std::vector<ShapeVertex> &vec);

}

