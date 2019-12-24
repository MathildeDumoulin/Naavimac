#ifndef INSTANCE_HPP__
#define INSTANCE_HPP__
#pragma once

#include <vector>
#include <glimac/common/Object.hpp>
#include <glimac/common/VertexArray.hpp>
#include <glimac/shading/ShadingProgram.hpp>
#include <glimac/common/Scene.hpp>

namespace glimac {


// Utiliser les stratégies pour modifier le vector m_offset en fonction du type de cube (et intégrer le changement de texture dans la statégie)
// Comme ça, on appelle le changement de stratégie, on refresh la liste des instances et on dessine les cubes avec la bonne texture !!
class Instances {
    private:
        GLuint m_buffer;
        std::vector<glm::vec3> m_offset;
        GLsizei m_nbIndexPerObj;

    public:
        Instances(const unsigned int nbInstances, const Object& obj, const VertexArray& vao);
        ~Instances();

        void createCubesGround();
        void refresh() const;

        const size_t nbInstances() const;
        const GLsizei nbIndexPerObj() const;
        bool isThereSomething(const glm::vec3& position) const;
        void addInstance(const glm::vec3& position);
        void drawInstances(const Scene& scene, const ShadingProgram& prog) const;
};

}

#endif