#ifndef MOUSE_HPP__
#define MOUSE_HPP__
#pragma once

#include <glimac/common/glm.hpp>
#include <glimac/gui/SDLWindowManager.hpp>
#include <glimac/common/Scene.hpp>
#include <glimac/common/CubeList.hpp>
#include <GL/glew.h>

#include "app/const.hpp"

namespace glimac {

class Mouse {
    private:
        glm::ivec2 m_position = glm::ivec2(0, 0);
        glm::ivec2 m_offsetCounter = glm::ivec2(0, 0);
        bool m_leftDown = false;
        bool m_middleDown = false;
        bool m_rightDown = false;

    public:
        Mouse() = default;
        ~Mouse() = default;

        bool leftDown() const;
        bool middleDown() const;
        bool rightDown() const;

        void leftDown(const bool val);
        void middleDown(const bool val);
        void rightDown(const bool val);

        const glm::ivec2 position() const;
        void updatePosition(const SDLWindowManager& window);
        void resetOffsetCounter();

        void updateSelection(Scene& scene, const CubeList& list);
        void updateSelectionMotion(Scene& scene, const SDLWindowManager& window, Instance& selectionInst);
};

}

#endif