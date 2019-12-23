#include "glimac/primitives/Cube.hpp"
#include <iostream>
#include <cassert>

namespace glimac {

/***** CLASS CUBE - METHODS *****/

    Cube::Cube() : m_Vertices(24), m_Indexes(36), m_nbVertex(0), m_nbIndex(0) {

        const std::vector<ShapeVertexHomo> quad = createQuad(1); //Create 4 vertices

        std::vector<glm::mat4> transforms = {
            glm::translate(glm::mat4(), glm::vec3(0, 0, 0.5)), //Front face
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(0, 0, -0.5)), glm::radians(180.f), glm::vec3(0, 1, 0)), //Back face
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(-0.5, 0, 0)), glm::radians(-90.f), glm::vec3(0, 1, 0)), //Left face
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(0.5, 0, 0)), glm::radians(90.f), glm::vec3(0, 1, 0)), //Right face
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(0, -0.5, 0)), glm::radians(90.f), glm::vec3(1, 0, 0)), //Bottom face
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(0, 0.5, 0)), glm::radians(-90.f), glm::vec3(1, 0, 0)) //Top face
        };

        for(const auto &mat:transforms) {
            std::vector<ShapeVertexHomo> face = quad; //Create a face from the 4 vertices

            transformShapeVertexVector(face, mat); //Put the face in the right place in 3D space
            pushQuad(face); //Push vertices and index in the Cube Data
        }
    }


    const ShapeVertex* Cube::verticesPointer() const {
        return &m_Vertices[0];
    }


    const GLsizei Cube::nbVertex() const {
        return m_nbVertex;
    }

    const uint32_t* Cube::indexesPointer() const {
        return &m_Indexes[0];
    }
    
    const GLsizei Cube::nbIndex() const {
        return m_nbIndex;
    }

    void Cube::pushQuad(const std::vector<ShapeVertexHomo> &quad) {
        assert(quad.size() == 4);

        uint32_t offset = m_nbVertex;       
        std::vector<uint32_t> newIndex = {
            offset+0, offset+1, offset+2, //First tri
            offset+1, offset+2, offset+3 //Second tri
        };
        
        m_Vertices.insert(m_Vertices.begin() + m_nbVertex, quad.cbegin(), quad.cend());
        m_Indexes.insert(m_Indexes.begin() + m_nbIndex, newIndex.cbegin(), newIndex.cend());

        m_nbVertex += 4;
        m_nbIndex += 6;
    }


/***** OTHERS FUNCTIONS *****/

    const std::vector<ShapeVertexHomo> createQuad(const float &size) {
        glm::vec2 texture(0.f, 0.f);
        glm::vec4 normal(0.f, 0.f, 1.f, 0.f);
        float depth = 0.f;
        float offset = size / 2.f;

        std::vector<ShapeVertexHomo> vertices = {
            ShapeVertexHomo(glm::vec4(-offset, offset, depth, 1), normal, texture), //Top Left
            ShapeVertexHomo(glm::vec4(-offset, -offset, depth, 1), normal, texture), //Bottom Left
            ShapeVertexHomo(glm::vec4(offset, offset, depth, 1), normal, texture), //Top Right
            ShapeVertexHomo(glm::vec4(offset, -offset, depth, 1), normal, texture) //Bottom Right
        };

        return vertices;
    }

}