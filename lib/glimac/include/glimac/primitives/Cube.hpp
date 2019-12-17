#pragma once 

#include <vector>

#include "glimac/common/ShapeVertex.hpp"

namespace glimac {

class Cube {
    private:
        std::vector<ShapeVertex> m_Vertices;
        GLsizei m_nVertexCount;
    
    public:
        Cube();

        const ShapeVertex* getDataPointer() const;
        GLsizei getVertexCount() const;
};


const std::vector<ShapeVertexHomo> createQuad(const float &size);
void pushQuadIntoVector(const std::vector<ShapeVertexHomo> &quad, std::vector<ShapeVertex> &vec);

}

