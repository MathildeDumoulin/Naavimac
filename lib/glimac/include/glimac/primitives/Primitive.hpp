#ifndef PRIMITIVE_HPP__
#define PRIMITIVE_HPP__
#pragma once

#include <vector>
#include <GL/glew.h>
#include "glimac/common/ShapeVertex.hpp"

namespace glimac {

template<typename T = ShapeVertex>
class Primitive {
    protected:
        std::vector<T> m_Vertices;
        std::vector<uint32_t> m_Indexes;
        GLsizei m_nbVertex;
        GLsizei m_nbIndex;
    
    public:
        Primitive(const size_t& sizeVertex, const size_t& sizeIndex)
            : m_Vertices(sizeVertex), m_Indexes(sizeIndex), m_nbVertex(0), m_nbIndex(0) {}


        const T* verticesPointer() const {
            return &m_Vertices[0];
        }

        std::vector<T>& vertices() {
            return m_Vertices;
        }

        const GLsizei nbVertex() const {
            return m_nbVertex;
        }
        
        const uint32_t* indexesPointer() const {
            return &m_Indexes[0];
        }

        std::vector<uint32_t>& indexes() {
            return m_Indexes;
        }

        const GLsizei nbIndex() const {
            return m_nbIndex;
        }
};

const std::vector<ShapeVertexHomo> createQuad(const float &size);

}

#endif