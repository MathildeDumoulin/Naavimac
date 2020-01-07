#ifndef LIGHT_CUBE_INST_HPP__
#define LIGHT_CUBE_INST_HPP__
#pragma once

#include <vector>
#include <glimac/common/Object.hpp>
#include <glimac/shading/ShadingProgram.hpp>
#include <glimac/common/Scene.hpp>
#include <glimac/common/Instance.hpp>

namespace glimac {

class LightCubeInst : public Instance {
    private:
        virtual void loadTextures(const std::string& diffuseFp) override;

    public:
        LightCubeInst(const unsigned int nbInstances, const Object& obj);
        ~LightCubeInst() = default;

        virtual const glm::vec3 getColor(const glm::vec3& position) const override;


        virtual void drawInstances(const Scene& scene, const ShadingProgram& prog, GLenum mode = GL_TRIANGLES) const override;
};

}

#endif