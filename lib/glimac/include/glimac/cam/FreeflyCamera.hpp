#ifndef FREEFLY_CAMERA_HPP__
#define FREEFLY_CAMERA_HPP__
#pragma once

#include "glimac/common/glm.hpp"

namespace glimac {

class FreeflyCamera {
    private:
        glm::vec3 m_position = glm::vec3(0.f, 10.f, 0.f);
        float m_fPhi = glm::pi<float>();
        float m_fTheta = 0.f;
        glm::vec3 m_frontVector;
        glm::vec3 m_leftVector;
        glm::vec3 m_upVector;

        void computeDirectionVectors();

    public:
        FreeflyCamera();
        void moveLeft(const float& t);
        void moveFront(const float& t);
        void moveUp(const float& t);
        void rotateLeft(const float& degrees);
        void rotateUp(const float& degrees);

        glm::mat4 getViewMatrix() const;
};

}

#endif