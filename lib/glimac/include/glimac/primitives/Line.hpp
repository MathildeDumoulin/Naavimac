#ifndef LINE_HPP__
#define LINE_HPP__
#pragma once

#include <vector>

#include "glimac/common/ShapeVertex.hpp"
#include <GL/glew.h>

namespace glimac {

class Line {
    private:
        std::vector<ShapeVertexHomo> m_Vertices;
        std::vector<uint32_t> m_Indexes;
        GLsizei m_nbVertex;
        GLsizei m_nbIndex;

        void pushQuad(const std::vector<ShapeVertexHomo> &quad);
    
    public:
        Line(const float& length, const float& thickness);

        const ShapeVertexHomo* verticesPointer() const;
        std::vector<ShapeVertexHomo>& vertices();
        const GLsizei nbVertex() const;
        
        const uint32_t* indexesPointer() const;
        std::vector<uint32_t>& indexes();
        const GLsizei nbIndex() const;

        void transform(const glm::mat4& mat);
};

}

#endif