#include "glimac/primitives/Line.hpp"
#include "glimac/primitives/Cube.hpp"
#include <iostream>
#include <cassert>

namespace glimac {

/***** CLASS LINE - METHODS *****/

    Line::Line(const float& length, const float& thickness) : m_Vertices(8), m_Indexes(36), m_nbVertex(0), m_nbIndex(0) {

        float offset = length/2.f;

        const std::vector<ShapeVertexHomo> quad = createQuad(thickness); //Create 4 vertices

        std::vector<glm::mat4> transforms = {
            glm::translate(glm::mat4(), glm::vec3(0, 0, offset)), //Front face
            glm::translate(glm::mat4(), glm::vec3(0, 0, -offset)) //Back face
        };

        // Fill Vertices Data
        for(const auto &mat:transforms) {
            std::vector<ShapeVertexHomo> face = quad; //Create a face from the 4 vertices

            transformShapeVertexVector(face, mat); //Put the face in the right place in 3D space
            m_Vertices.insert(m_Vertices.begin() + m_nbVertex, face.cbegin(), face.cend());
            m_nbVertex += 4;
        }

        // Fill Indexes Data
        std::vector<uint32_t> indexes = {
            0, 1, 2, 1, 2, 3,
            4, 5, 6, 5, 6, 7,
            0, 2, 4, 2, 4, 6,
            1, 3, 5, 3, 5, 7,
            2, 3, 6, 3, 6, 7,
            0, 1, 4, 1, 4, 5
        };
        m_Indexes.insert(m_Indexes.begin() + m_nbIndex, indexes.cbegin(), indexes.cend());
        m_nbIndex += 36;
    }


    const ShapeVertexHomo* Line::verticesPointer() const {
        return &m_Vertices[0];
    }

    std::vector<ShapeVertexHomo>& Line::vertices() {
        return m_Vertices;
    }


    const GLsizei Line::nbVertex() const {
        return m_nbVertex;
    }

    const uint32_t* Line::indexesPointer() const {
        return &m_Indexes[0];
    }

    std::vector<uint32_t>& Line::indexes() {
        return m_Indexes;
    }
    
    const GLsizei Line::nbIndex() const {
        return m_nbIndex;
    }

    void Line::transform(const glm::mat4& mat) {
        for(auto &elt:m_Vertices) {
            elt.transform(mat);
        }
    }
}