#include "glimac/cam/FreeflyCamera.hpp"
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
    glm::vec3 horizontalAxis(0,0,0);

    float x = m_leftVector.x;
    float y = m_leftVector.y;
    float z = m_leftVector.z;

    if(abs(x) >= abs(y) && abs(x) >= abs(z)) {
        horizontalAxis = glm::vec3(1, 0, 0);
        if(x >= 0) horizontalAxis = -horizontalAxis;
    }
    else if(abs(y) >= abs(x) && abs(y) >= abs(z)) {
        horizontalAxis = glm::vec3(0, 1, 0);
        if(y >= 0) horizontalAxis = -horizontalAxis;
    }
    else if(abs(z) >= abs(x) && abs(z) >= abs(y)){
        horizontalAxis = glm::vec3(0, 0, 1);
        if(z >= 0) horizontalAxis = -horizontalAxis;
    }

    return horizontalAxis;
}


const glm::vec3 FreeflyCamera::dominantVerticalAxis() const {
    glm::vec3 verticalAxis(0,0,0);

    float x = m_upVector.x;
    float y = m_upVector.y;
    float z = m_upVector.z;

    if(abs(x) >= abs(y) && abs(x) >= abs(z)) {
        verticalAxis = glm::vec3(1, 0, 0);
        if(x <= 0) verticalAxis = -verticalAxis;
    }
    else if(abs(y) >= abs(x) && abs(y) >= abs(z)) {
        verticalAxis = glm::vec3(0, 1, 0);
        if(y <= 0) verticalAxis = -verticalAxis;
    }
    else if(abs(z) >= abs(x) && abs(z) >= abs(y)){
        verticalAxis = glm::vec3(0, 0, 1);
        if(z <= 0) verticalAxis = -verticalAxis;
    }

    return verticalAxis;
}

}