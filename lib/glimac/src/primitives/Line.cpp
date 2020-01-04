#include "glimac/primitives/Line.hpp"
#include "glimac/primitives/Cube.hpp"
#include <iostream>
#include <cassert>

namespace glimac {

/***** CLASS LINE - METHODS *****/

    Line::Line(const float& length) : Primitive(2, 2) {
        float offset = length/2.f;

        // Fill Vertices Data
        glm::vec4 normal(0.f, 0.f, 1.f, 0.f);
        glm::vec2 texCoords(0.f, 0.f);

        std::vector<ShapeVertexHomo> vertices = {
            ShapeVertexHomo(glm::vec4(-offset, 0, 0, 1), normal, texCoords),
            ShapeVertexHomo(glm::vec4(offset, 0, 0, 1), normal, texCoords)
        };

        m_Vertices.insert(m_Vertices.begin(), vertices.cbegin(), vertices.cend());
        m_nbVertex += 2;


        // Fill Indexes Data
        std::vector<uint32_t> indexes = {0, 1};
        m_Indexes.insert(m_Indexes.begin(), indexes.cbegin(), indexes.cend());
        m_nbIndex += 2;
    }


    void Line::transform(const glm::mat4& mat) {
        for(auto &elt:m_Vertices) {
            elt.transform(mat);
        }
    }
}