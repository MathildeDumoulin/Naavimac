#include "glimac/gui/Mouse.hpp"
#include <iostream>

namespace glimac {

    const bool Mouse::leftDown() const {
        return m_leftDown;
    }
    const bool Mouse::middleDown() const {
        return m_middleDown;
    }
    const bool Mouse::rightDown() const {
        return m_rightDown;
    }

    void Mouse::leftDown(const bool val) {
        m_leftDown = val;
    }
    void Mouse::middleDown(const bool val) {
        m_middleDown = val;
    }
    void Mouse::rightDown(const bool val) {
        m_rightDown = val;
    }

    const glm::ivec2 Mouse::position() const {
        return m_position;
    }

    void Mouse::updatePosition(const SDLWindowManager& window) {
        m_position = window.getMousePosition();
    }

    void Mouse::updateSelection(Scene& scene, const CubeList& list) const {
        //Read inside the frame buffer to get depth information
        //Transform mouse window coords into world coords
        GLfloat depth;
        glReadPixels(m_position.x, windowHeight - m_position.y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glm::vec4 viewport = glm::vec4(0, 0, windowWidth, windowHeight);
        glm::vec3 winCoord = glm::vec3(m_position.x, windowHeight - m_position.y - 1, depth);
        glm::vec3 objCoord = glm::unProject(winCoord, scene.viewMatrix(), scene.projMat(), viewport);

        //Round coords
        glm::vec3 realObjCoord(
            (objCoord.x >= 0) ? floor(objCoord.x + 0.5) : ceil(objCoord.x - 0.5),
            (objCoord.y >= 0) ? floor(objCoord.y + 0.5) : ceil(objCoord.y - 0.5),
            (objCoord.z >= 0) ? floor(objCoord.z + 0.5) : ceil(objCoord.z - 0.5)
        );

        //Affect coords to the selection
        scene.selection(realObjCoord);

        //If the realObjCoord is actually an empty cube, recalculate a new selection at the good spot on the window
        if(list.type(realObjCoord) == NONE) {
            glm::vec3 newCoord = scene.cam().position() + 10.0f*glm::normalize(realObjCoord - scene.cam().position());
            newCoord = glm::vec3(
                (newCoord.x >= 0) ? floor(newCoord.x + 0.5) : ceil(newCoord.x - 0.5),
                (newCoord.y >= 0) ? floor(newCoord.y + 0.5) : ceil(newCoord.y - 0.5),
                (newCoord.z >= 0) ? floor(newCoord.z + 0.5) : ceil(newCoord.z - 0.5)
            );
            scene.selection(newCoord);
        }

    }

    void Mouse::updateSelectionMotion(Scene& scene, const SDLWindowManager& window, Instance& inst) {
        glm::ivec2 offsetPosition = window.getMousePosition() - m_position;
        updatePosition(window);

        glm::vec3 currentSelection = scene.selection();

        int step = 6;

        if(abs(offsetPosition.x) >= abs(offsetPosition.y)) offsetPosition.y = 0; else offsetPosition.x = 0;

        if(offsetPosition.x > 0) ++m_offsetCounter.x; else if(offsetPosition.x < 0) --m_offsetCounter.x;

        if(offsetPosition.y > 0) ++m_offsetCounter.y; else if(offsetPosition.y < 0) --m_offsetCounter.y;

        if(m_offsetCounter.x >= step) { scene.selection(glm::vec3(currentSelection.x + 1, currentSelection.y, currentSelection.z)); m_offsetCounter.x = 0; }
        if(m_offsetCounter.x <= -step) { scene.selection(glm::vec3(currentSelection.x - 1, currentSelection.y, currentSelection.z)); m_offsetCounter.x = 0; }

        if(m_offsetCounter.y >= step) { scene.selection(glm::vec3(currentSelection.x, currentSelection.y - 1, currentSelection.z)); m_offsetCounter.y = 0; }
        if(m_offsetCounter.y <= -step) { scene.selection(glm::vec3(currentSelection.x, currentSelection.y + 1, currentSelection.z)); m_offsetCounter.y = 0; }

        if(scene.selection() != currentSelection) inst.changeFirstInstance(scene.selection());
    }

}