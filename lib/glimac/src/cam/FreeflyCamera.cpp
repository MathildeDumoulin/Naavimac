#include "glimac/cam/FreeflyCamera.hpp"
#include "glimac/common/math.hpp"
#include <cmath>

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

const glm::vec3 FreeflyCamera::frontVector() const {
    return m_frontVector;
}

const glm::vec3 FreeflyCamera::leftVector() const {
    return m_leftVector;
}

const glm::vec3 FreeflyCamera::upVector() const {
    return m_upVector;
}


const glm::vec3 FreeflyCamera::dominantHorizontalAxis() const {
    glm::vec3 horizontalAxis = -dominantAxis(m_leftVector);

    return horizontalAxis;
}


const glm::vec3 FreeflyCamera::dominantVerticalAxis() const {
    glm::vec3 verticalAxis = dominantAxis(m_upVector);

    return verticalAxis;
}

}