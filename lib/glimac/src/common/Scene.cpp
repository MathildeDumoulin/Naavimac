#include "glimac/common/Scene.hpp"

namespace glimac {

FreeflyCamera& Scene::cam() {
    return m_cam;
}

glm::vec3& Scene::selection() {
    return m_selection;
}

glm::mat4 Scene::viewMatrix() const {
    return m_cam.getViewMatrix();
}

glm::mat4 Scene::projMat() const {
    return m_projMat;
}

}