#include "glimac/primitives/CubeEdges.hpp"
#include "glimac/primitives/Line.hpp"
#include <iostream>
#include <cassert>
#include <algorithm>

namespace glimac {

/***** CLASS CUBE EDGES - METHODS *****/

    CubeEdges::CubeEdges(const float& thickness) : Primitive(96, 432) {
        const Line line(1+thickness, thickness);

        float offset = 1/2.f;

        std::vector<glm::mat4> transforms = {
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(-offset, 0, offset)), glm::radians(90.f), glm::vec3(1, 0, 0)), //Front face 1
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(0, -offset, offset)), glm::radians(90.f), glm::vec3(0, 1, 0)), //Front face 2
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(offset, 0, offset)), glm::radians(90.f), glm::vec3(1, 0, 0)), //Front face 3
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(0, offset, offset)), glm::radians(90.f), glm::vec3(0, 1, 0)), //Front face 4
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(-offset, 0, -offset)), glm::radians(90.f), glm::vec3(1, 0, 0)), //Back face 1
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(0, -offset, -offset)), glm::radians(90.f), glm::vec3(0, 1, 0)), //Back face 2
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(offset, 0, -offset)), glm::radians(90.f), glm::vec3(1, 0, 0)), //Back face 3
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(0, offset, -offset)), glm::radians(90.f), glm::vec3(0, 1, 0)), //Back face 4
            glm::translate(glm::mat4(), glm::vec3(-offset, offset, 0)), //Left side 1
            glm::translate(glm::mat4(), glm::vec3(-offset, -offset, 0)), //Left side 2
            glm::translate(glm::mat4(), glm::vec3(offset, offset, 0)), //Right side 1
            glm::translate(glm::mat4(), glm::vec3(offset, -offset, 0)) //Right side 2
        };

        for(const auto &mat:transforms) {
            Line currentLine = line; //Create a new line

            currentLine.transform(mat); //Put the line in the right place in 3D space
            pushLine(currentLine); //Push VBO and IBO into CubeEdges data
        }
    }


    void CubeEdges::pushLine(Line& line) {
        
        uint32_t offset = m_nbVertex;       

        std::for_each(line.indexes().begin(), line.indexes().end(), [offset](uint32_t& val) {val += offset;});
        
        m_Vertices.insert(m_Vertices.begin() + m_nbVertex, line.vertices().cbegin(), line.vertices().cend());
        m_Indexes.insert(m_Indexes.begin() + m_nbIndex, line.indexes().cbegin(), line.indexes().cend());

        m_nbVertex += 8;
        m_nbIndex += 36;
    }
}