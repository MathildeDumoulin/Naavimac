#include "glimac/cam/FreeflyCamera.hpp"

namespace glimac {

void FreeflyCamera::computeDirectionVectors() {
    m_frontVector = glm::vec3(
        glm::cos(m_fTheta) * glm::sin(m_fPhi),
        glm::sin(m_fTheta),
        glm::cos(m_fTheta) * glm::cos(m_fPhi)
    );

    m_leftVector = glm::vec3(
        glm::sin(m_fPhi + glm::half_pi<float>()),
        0,
        glm::cos(m_fPhi + glm::half_pi<float>())
    );

    m_upVector = glm::cross(m_frontVector, m_leftVector);
}

FreeflyCamera::FreeflyCamera() {
    computeDirectionVectors();
}

void FreeflyCamera::moveLeft(const float& t) {
    m_position += t*m_leftVector;
    computeDirectionVectors();
}

void FreeflyCamera::moveFront(const float& t) {
    m_position += t*m_frontVector;
    computeDirectionVectors();
}

void FreeflyCamera::moveUp(const float& t) {
    m_position += t*m_upVector;
    computeDirectionVectors();
}

void FreeflyCamera::rotateLeft(const float& degrees) {
    m_fPhi += glm::radians(degrees);
    computeDirectionVectors();
}

void FreeflyCamera::rotateUp(const float& degrees) {
    m_fTheta += glm::radians(degrees);
    computeDirectionVectors();
}

glm::mat4 FreeflyCamera::getViewMatrix() const {
    return glm::lookAt(m_position, m_position+m_frontVector, m_upVector);
}

const glm::vec3 FreeflyCamera::position() const {
    return m_position;
}

}