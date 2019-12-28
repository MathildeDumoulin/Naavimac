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
        GLfloat depth;
        glReadPixels(m_position.x, windowHeight - m_position.y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glm::vec4 viewport = glm::vec4(0, 0, windowWidth, windowHeight);
        glm::vec3 winCoord = glm::vec3(m_position.x, windowHeight - m_position.y - 1, depth);
        glm::vec3 objCoord = glm::unProject(winCoord, scene.viewMatrix(), scene.projMat(), viewport);

        glm::vec3 realObjCoord(
            (objCoord.x >= 0) ? floor(objCoord.x + 0.5) : ceil(objCoord.x - 0.5),
            (objCoord.y >= 0) ? floor(objCoord.y + 0.5) : ceil(objCoord.y - 0.5),
            (objCoord.z >= 0) ? floor(objCoord.z + 0.5) : ceil(objCoord.z - 0.5)
        );

        scene.selection() = realObjCoord;
        if(list.type(scene.selection()) == NONE) {
            scene.selection() = scene.cam().position() + 10.0f*glm::normalize(scene.selection() - scene.cam().position());
            scene.selection() = glm::vec3(
                (scene.selection().x >= 0) ? floor(scene.selection().x + 0.5) : ceil(scene.selection().x - 0.5),
                (scene.selection().y >= 0) ? floor(scene.selection().y + 0.5) : ceil(scene.selection().y - 0.5),
                (scene.selection().z >= 0) ? floor(scene.selection().z + 0.5) : ceil(scene.selection().z - 0.5)
            );
        }
        std::cout << objCoord << scene.selection() << std::endl;
    }

}