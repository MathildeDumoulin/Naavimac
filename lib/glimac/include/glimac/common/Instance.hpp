#ifndef INSTANCE_HPP__
#define INSTANCE_HPP__
#pragma once

#include <vector>
#include <glimac/common/Object.hpp>
#include <glimac/shading/ShadingProgram.hpp>
#include <glimac/common/Scene.hpp>

namespace glimac {

class Instance {
    protected:
        GLuint m_vao;
        GLuint m_bufferPosition;
        std::vector<glm::vec3> m_offsetPosition;
        GLsizei m_nbIndexPerObj;

        virtual void loadTextures(const std::string& diffuseFp) = 0;

        void generateVertexArray(const Object& obj);

    public:
        Instance(const unsigned int nbInstances, const Object& obj);
        virtual ~Instance();
        virtual void refresh() const;

        const size_t nbInstances() const;
        const GLsizei nbIndexPerObj() const;
        std::vector<glm::vec3>& offsetPosition();
        virtual const glm::vec3 getColor(const glm::vec3& position) const;

        bool isThereSomething(const glm::vec3& position) const;
        virtual void addInstance(const glm::vec3& position, const glm::vec3& color = glm::vec3(1.f,1.f,1.f)) = 0;
        virtual void removeInstance(const glm::vec3& position) = 0;
        void changeFirstInstance(const glm::vec3& position);

        virtual void drawInstances(const Scene& scene, const ShadingProgram& prog, GLenum mode = GL_TRIANGLES) const = 0;
};

}

#endif