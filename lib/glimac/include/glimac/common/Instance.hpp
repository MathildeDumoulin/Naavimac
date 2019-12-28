#ifndef INSTANCE_HPP__
#define INSTANCE_HPP__
#pragma once

#include <vector>
#include <glimac/common/Object.hpp>
#include <glimac/common/VertexArray.hpp>
#include <glimac/shading/ShadingProgram.hpp>
#include <glimac/common/Scene.hpp>

namespace glimac {

class Instance {
    private:
        VertexArray m_vao;
        GLuint m_buffer;
        std::vector<glm::vec3> m_offsetPosition;
        GLsizei m_nbIndexPerObj;

    public:
        Instance(const unsigned int nbInstances, const Object& obj);
        ~Instance();
        void refresh() const;

        const size_t nbInstances() const;
        const GLsizei nbIndexPerObj() const;
        std::vector<glm::vec3>& offsetPosition();
        const VertexArray& vao() const;

        bool isThereSomething(const glm::vec3& position) const;
        void addInstance(const glm::vec3& position);
        void removeInstance(const glm::vec3& position);

        void drawInstances(const Scene& scene, const ShadingProgram& prog) const;
};

}

#endif