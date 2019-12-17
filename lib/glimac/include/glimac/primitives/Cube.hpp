#pragma once 

#include <vector>

#include "glimac/common/ShapeVertex.hpp"

namespace glimac {

class Cube {
    private:
        std::vector<ShapeVertex> m_Vertices;
        std::vector<uint32_t> m_Indexes;
        GLsizei m_nbVertex;
        GLsizei m_nbIndex;

        void pushQuad(const std::vector<ShapeVertexHomo> &quad);
    
    public:
        Cube();

        const ShapeVertex* getVerticesPointer() const;
        const GLsizei getVertexCount() const;
        
        const uint32_t* getIndexesPointer() const;
        const GLsizei getIndexCount() const;
};


const std::vector<ShapeVertexHomo> createQuad(const float &size);

}

