#ifndef CUBE_EDGES_HPP__
#define CUBE_EDGES_HPP__
#pragma once

#include <vector>

#include "glimac/common/ShapeVertex.hpp"
#include "glimac/primitives/Line.hpp"

namespace glimac {

class CubeEdges {
    private:
        std::vector<ShapeVertex> m_Vertices;
        std::vector<uint32_t> m_Indexes;
        GLsizei m_nbVertex;
        GLsizei m_nbIndex;

        void pushLine(Line& line);
    
    public:
        CubeEdges(const float& thickness);

        const ShapeVertex* verticesPointer() const;
        const GLsizei nbVertex() const;
        
        const uint32_t* indexesPointer() const;
        const GLsizei nbIndex() const;
};

}

#endif