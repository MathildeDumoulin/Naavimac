#ifndef INSTANCE_HPP__
#define INSTANCE_HPP__
#pragma once

#include <vector>
#include <glimac/common/Object.hpp>
#include <glimac/shading/ShadingProgram.hpp>
#include <glimac/common/Scene.hpp>

namespace glimac {

class Instance {
    private:
        GLuint m_vao;
        GLuint m_buffer;
        std::vector<glm::vec3> m_offsetPosition;
        GLsizei m_nbIndexPerObj;

        GLuint m_diffuseTexture;

        void loadTextures(const std::string& diffuseFp);

        void generateVertexArray(const Object& obj);

    public:
        Instance(const unsigned int nbInstances, const Object& obj, const std::string& diffuseFp = "");
        ~Instance();
        void refresh() const;

        const size_t nbInstances() const;
        const GLsizei nbIndexPerObj() const;
        std::vector<glm::vec3>& offsetPosition();

        bool isThereSomething(const glm::vec3& position) const;
        void addInstance(const glm::vec3& position);
        void removeInstance(const glm::vec3& position);
        void changeFirstInstance(const glm::vec3& position);

        void drawInstances(const Scene& scene, const ShadingProgram& prog, GLenum mode = GL_TRIANGLES) const;
};

}

#endif