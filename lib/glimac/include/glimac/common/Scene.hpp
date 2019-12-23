#ifndef SCENE_HPP__
#define SCENE_HPP__
#pragma once

#include "app/const.hpp"
#include "glimac/cam/FreeflyCamera.hpp"
#include "glimac/common/glm.hpp"

namespace glimac {

class Scene {
    private:
        FreeflyCamera m_cam;
        glm::mat4 m_projMat = glm::perspective(glm::radians(camViewAngle), float(windowWidth)/float(windowHeight), nearClipPlane, farClipPlane);
        glm::vec3 m_selection = glm::vec3(0.f, 0.f, 0.f);

    public:
        Scene() = default;

        FreeflyCamera& cam();
        glm::vec3& selection();
        glm::mat4 viewMatrix() const;
        glm::mat4 projMat() const;

};

}

#endif