#include "glimac/primitives/CubeEdges.hpp"
#include <iostream>
#include <cassert>
#include <algorithm>

namespace glimac {

/***** CLASS CUBE EDGES - METHODS *****/

    CubeEdges::CubeEdges() : Primitive(8, 24) {

        const std::vector<ShapeVertexHomo> quad = createQuad(1); //Create 4 vertices

        std::vector<glm::mat4> transforms = {
            glm::translate(glm::mat4(), glm::vec3(0, 0, 0.5)), //Front face
            glm::translate(glm::mat4(), glm::vec3(0, 0, -0.5)) //Back face
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
            0, 1, 0, 2, 0, 4,
            1, 3, 1, 5,
            2, 3, 2, 6,
            3, 7,
            4, 5, 4, 6,
            5, 7,
            6, 7
        };
        m_Indexes.insert(m_Indexes.begin() + m_nbIndex, indexes.cbegin(), indexes.cend());
        m_nbIndex += 24;
    }

}