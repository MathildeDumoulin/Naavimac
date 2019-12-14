#include "glimac/primitives/Cube.hpp"
#include <iostream>
#include <cassert>

namespace glimac {


// FAIRE UN TABLEAU DE MATRICES PUIS BOUCLER DESSUS (SANS IBO)
Cube::Cube() : m_nVertexCount(0) {

    const std::vector<ShapeVertexHomo> face = createSquareFace(0.5f);

    //FACE AVANT
    std::vector<ShapeVertexHomo> vertices = face;
    glm::mat4 transform = glm::translate(glm::mat4(), glm::vec3(0, 0, 0.5));

    transformShapeVertexVector(vertices, transform);
    pushQuadIntoVector(vertices, m_Vertices);
    m_nVertexCount += 6;

    //FACE ARRIERE
    vertices = face;
    transform = glm::translate(glm::mat4(), glm::vec3(0, 0, -0.5));
    transform = glm::rotate(transform, glm::radians(180.f), glm::vec3(0, 1, 0));

    transformShapeVertexVector(vertices, transform);
    pushQuadIntoVector(vertices, m_Vertices);
    m_nVertexCount += 6;

    //FACE GAUCHE
    vertices = face;
    transform = glm::translate(glm::mat4(), glm::vec3(-0.5, 0, 0));
    transform = glm::rotate(transform, glm::radians(-90.f), glm::vec3(0, 1, 0));

    transformShapeVertexVector(vertices, transform);
    pushQuadIntoVector(vertices, m_Vertices);
    m_nVertexCount += 6;

    //FACE DROITE
    vertices = face;
    transform = glm::translate(glm::mat4(), glm::vec3(0.5, 0, 0));
    transform = glm::rotate(transform, glm::radians(90.f), glm::vec3(0, 1, 0));

    transformShapeVertexVector(vertices, transform);
    pushQuadIntoVector(vertices, m_Vertices);
    m_nVertexCount += 6;

    //FACE BAS
    vertices = face;
    transform = glm::translate(glm::mat4(), glm::vec3(0, -0.5, 0));
    transform = glm::rotate(transform, glm::radians(90.f), glm::vec3(1, 0, 0));

    transformShapeVertexVector(vertices, transform);
    pushQuadIntoVector(vertices, m_Vertices);
    m_nVertexCount += 6;

    //FACE HAUT
    vertices = face;
    transform = glm::translate(glm::mat4(), glm::vec3(0, 0.5, 0));
    transform = glm::rotate(transform, glm::radians(-90.f), glm::vec3(1, 0, 0));

    transformShapeVertexVector(vertices, transform);
    pushQuadIntoVector(vertices, m_Vertices);
    m_nVertexCount += 6;

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


const std::vector<ShapeVertexHomo> createSquareFace(const float &size) {
    glm::vec2 texture(0.f, 0.f);
    glm::vec4 normal(0.f, 0.f, 1.f, 0.f);
    float depth = 0.f;

    std::vector<ShapeVertexHomo> vertices = {
        ShapeVertexHomo(glm::vec4(-size, size, depth, 1), normal, texture), //Top Left
        ShapeVertexHomo(glm::vec4(-size, -size, depth, 1), normal, texture), //Bottom Left
        ShapeVertexHomo(glm::vec4(size, size, depth, 1), normal, texture), //Top Right
        ShapeVertexHomo(glm::vec4(size, -size, depth, 1), normal, texture) //Bottom Right
    };

    return vertices;
}

void transformShapeVertex(ShapeVertexHomo &pt, const glm::mat4 &mat) {
    pt.position = mat * pt.position;
    pt.normal = mat * pt.normal;
}

void transformShapeVertexVector(std::vector<ShapeVertexHomo> &vec, const glm::mat4 &mat) {
    for(auto &v:vec) {
        transformShapeVertex(v, mat);
    }
}

void pushQuadIntoVector(std::vector<ShapeVertexHomo> &quad, std::vector<ShapeVertex> &vec) {
    assert(quad.size() == 4);

    vec.push_back(quad[0]); //Convert automatically from ShapeVertexHomo to ShapeVertex
    vec.push_back(quad[1]);
    vec.push_back(quad[2]);

    vec.push_back(quad[1]);
    vec.push_back(quad[2]);
    vec.push_back(quad[3]);
}

}