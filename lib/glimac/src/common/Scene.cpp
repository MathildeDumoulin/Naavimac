#include "glimac/common/Scene.hpp"

namespace glimac {

FreeflyCamera& Scene::cam() {
    return m_cam;
}

const glm::vec3& Scene::selection() const {
    return m_selection;
}

void Scene::selection(const glm::vec3& vec) {
    if(vec.x >= worldMinX && vec.x <= worldMaxX && 
        vec.y >= worldMinY && vec.y <= worldMaxY && 
            vec.z >= worldMinZ && vec.z <= worldMaxZ) {
                m_selection = vec;
            }
}

void Scene::moveSelection(const glm::vec3& vec) {
    glm::vec3 newSelection = m_selection;

    newSelection.x += vec.x;
    newSelection.y += vec.y;
    newSelection.z += vec.z;

    selection(newSelection); //Update the position of the selection
}

const glm::vec3& Scene::faceAxis() const {
    return m_faceAxis;
}

void Scene::faceAxis(const glm::vec3& vec) {
    m_faceAxis = vec;
}

glm::mat4 Scene::viewMatrix() const {
    return m_cam.getViewMatrix();
}

glm::mat4 Scene::projMat() const {
    return m_projMat;
}

}