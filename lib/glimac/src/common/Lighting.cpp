#include "glimac/common/Lighting.hpp"
#include <algorithm>
#include <iostream>

namespace glimac {

void Lighting::sunLightDir(const glm::vec3& dir) {
    m_sunLightDir = dir;
}

const glm::vec3& Lighting::sunLightDir() const {
    return m_sunLightDir;
}

void Lighting::sunLightInt(const glm::vec3& intensity) {
    m_sunLightInt = intensity;
}

const glm::vec3& Lighting::sunLightInt() const {
    return m_sunLightInt;
}

void Lighting::pointLightsInt(const glm::vec3& intensity) {
    m_pointLightsInt = intensity;
}

const glm::vec3& Lighting::pointlightsInt() const {
    return m_pointLightsInt;
}

const unsigned int Lighting::nbLights() const {
    return m_pointLights.size();
}   

void Lighting::activateSun() {
    m_sunLightInt = glm::vec3(1, 1, 1);
}

void Lighting::deactivateSun() {
    m_sunLightInt = glm::vec3(0, 0, 0);
}

bool Lighting::addLight(const glm::vec3& position) {
    if(m_pointLights.size() >= nbLightsMax) return false;

    for(const auto &elt:m_pointLights) {
        if(elt == position) return false;
    }

    m_pointLights.push_back(position);
    return true;
}

bool Lighting::removeLight(const glm::vec3& position) {
    bool isThere = false;
    for(const auto &elt:m_pointLights) {
        if(elt == position) isThere = true;
    }
    if(isThere) {
        m_pointLights.erase(std::remove(m_pointLights.begin(), m_pointLights.end(), position), m_pointLights.end());
    }
    return isThere;
}

void Lighting::sendLights(const ShadingProgram& prog) const {
    glUniform3fv(prog.uSunLightDir, 1, glm::value_ptr(m_sunLightDir));
    glUniform3fv(prog.uSunLightInt, 1, glm::value_ptr(m_sunLightInt));

    glUniform3fv(prog.uPointLightsInt, 1, glm::value_ptr(m_pointLightsInt));
    glUniform3fv(prog.uPointLights, m_pointLights.size(), glm::value_ptr(m_pointLights[0]));
    glUniform1i(prog.uNbLight, m_pointLights.size());
}

}