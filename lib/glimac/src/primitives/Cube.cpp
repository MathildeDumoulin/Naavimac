#include "glimac/primitives/Cube.hpp"
#include <iostream>
#include <cassert>

namespace glimac {

/***** CLASS CUBE - METHODS *****/

    // (SANS IBO)
    Cube::Cube() : m_nVertexCount(0) {

        const std::vector<ShapeVertexHomo> quad = createQuad(1);

        std::vector<glm::mat4> transforms = {
            glm::translate(glm::mat4(), glm::vec3(0, 0, 0.5)), //Front face
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(0, 0, -0.5)), glm::radians(180.f), glm::vec3(0, 1, 0)), //Back face
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(-0.5, 0, 0)), glm::radians(-90.f), glm::vec3(0, 1, 0)), //Left face
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(0.5, 0, 0)), glm::radians(90.f), glm::vec3(0, 1, 0)), //Right face
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(0, -0.5, 0)), glm::radians(90.f), glm::vec3(1, 0, 0)), //Bottom face
            glm::rotate(glm::translate(glm::mat4(), glm::vec3(0, 0.5, 0)), glm::radians(-90.f), glm::vec3(1, 0, 0)) //Top face
        };

        for(const auto &mat:transforms) {
            std::vector<ShapeVertexHomo> face = quad;

            transformShapeVertexVector(face, mat);
            pushQuadIntoVector(face, m_Vertices);
            m_nVertexCount += 6;
        }

        /*
        for(const auto &v:m_Vertices) {
            std::cout << v.normal << std::endl;
        }
        */
    }


    const ShapeVertex* Cube::getDataPointer() const {
        return &m_Vertices[0];
    }


    GLsizei Cube::getVertexCount() const {
        return m_nVertexCount;
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


    void pushQuadIntoVector(const std::vector<ShapeVertexHomo> &quad, std::vector<ShapeVertex> &vec) {
        assert(quad.size() == 4);

        //First tri
        vec.push_back(quad[0]); //Convert automatically from ShapeVertexHomo to ShapeVertex
        vec.push_back(quad[1]);
        vec.push_back(quad[2]);

        //Second tri
        vec.push_back(quad[1]);
        vec.push_back(quad[2]);
        vec.push_back(quad[3]);
    }

}