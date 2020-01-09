#ifndef LIGHTING_HPP__
#define LIGHTING_HPP__
#pragma once

#include <GL/glew.h>
#include <glimac/common/glm.hpp>
#include <glimac/shading/ShadingProgram.hpp>
#include <vector>
#include "app/const.hpp"

namespace glimac {

class Lighting {
    private:
        glm::vec3 m_sunLightDir = glm::vec3(1, 1, 0);
        glm::vec3 m_sunLightInt = glm::vec3(1, 1, 1);

        std::vector<glm::vec3> m_pointLights;
        glm::vec3 m_pointLightsInt = glm::vec3(5, 5, 5);

    public:
        Lighting() = default;
        ~Lighting() = default;

        void sunLightDir(const glm::vec3& dir);
        const glm::vec3& sunLightDir() const;
        void sunLightInt(const glm::vec3& intensity);
        const glm::vec3& sunLightInt() const;

        void pointLightsInt(const glm::vec3& intensity);
        const glm::vec3& pointlightsInt() const;
        unsigned int nbLights() const;

        void activateSun();
        void deactivateSun();

        bool addLight(const glm::vec3& position);
        bool removeLight(const glm::vec3& position);

        void sendLights(const ShadingProgram& prog) const;

};

}

#endif