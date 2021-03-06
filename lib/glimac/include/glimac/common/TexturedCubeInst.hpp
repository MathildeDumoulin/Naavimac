#ifndef TEXTURED_CUBE_INST_HPP__
#define TEXTURED_CUBE_INST_HPP__
#pragma once

#include <vector>
#include <glimac/common/Object.hpp>
#include <glimac/shading/ShadingProgram.hpp>
#include <glimac/common/Scene.hpp>
#include <glimac/common/Instance.hpp>

namespace glimac {

class TexturedCubeInst : public Instance {
    private:
        GLuint m_diffuseTexture;

        virtual void loadTextures(const std::string& diffuseFp) override;

    public:
        TexturedCubeInst(const unsigned int nbInstances, const Object& obj, const std::string& diffuseFp = "");
        ~TexturedCubeInst();

        virtual void drawInstances(const Scene& scene, const ShadingProgram& prog, GLenum mode = GL_TRIANGLES) const override;
};

}

#endif