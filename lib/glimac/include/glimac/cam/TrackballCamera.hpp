#ifndef TRACKBALL_CAMERA_HPP__
#define TRACKBALL_CAMERA_HPP__
#pragma once

#include "glimac/common/glm.hpp"

namespace glimac {

class TrackballCamera {
    private:
        float m_fDistance;
        float m_fAngleX;
        float m_fAngleY;

    public:
        TrackballCamera();

        void moveFront(float delta);
        void rotateLeft(float degrees);
        void rotateUp(float degrees);

        glm::mat4 getViewMatrix() const;
};

}

#endif