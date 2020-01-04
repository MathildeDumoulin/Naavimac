#ifndef COLOR_CUBE_INST_HPP__
#define COLOR_CUBE_INST_HPP__
#pragma once

#include <vector>
#include <glimac/common/Object.hpp>
#include <glimac/shading/ShadingProgram.hpp>
#include <glimac/common/Scene.hpp>
#include <glimac/common/Instance.hpp>

namespace glimac {

class ColorCubeInst : public Instance {
    private:
        GLuint m_bufferColor;
        std::vector<glm::vec3> m_offsetColor;

        virtual void loadTextures(const std::string& diffuseFp) override;

    public:
        ColorCubeInst(const unsigned int nbInstances, const Object& obj);
        ~ColorCubeInst();
        virtual void refresh() const override;

        virtual const glm::vec3 getColor(const glm::vec3& position) const override;

        virtual void addInstance(const glm::vec3& position, const glm::vec3& color = glm::vec3(1.f,1.f,1.f)) override;
        virtual void removeInstance(const glm::vec3& position) override;

        virtual void drawInstances(const Scene& scene, const ShadingProgram& prog, GLenum mode = GL_TRIANGLES) const override;
};

}

#endif