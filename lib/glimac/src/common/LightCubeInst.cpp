#include "glimac/common/LightCubeInst.hpp"
#include <glimac/common/Image.hpp>
#include <iostream>
#include <GL/glew.h>

#include <glimac/common/Object.hpp>

#include "app/const.hpp"

#include <algorithm>

namespace glimac {

/***** CONSTRUCTORS & DESTRUCTOR *****/

    LightCubeInst::LightCubeInst(const unsigned int nbInstances, const Object& obj) 
        : Instance(nbInstances, obj) {}


/***** PRIVATE METHODS *****/

    void LightCubeInst::loadTextures(const std::string& diffuseFp) {
        //DO NOTHING
    }

/***** GETTERS & SETTERS *****/

    const glm::vec3 LightCubeInst::getColor(const glm::vec3& position) const {
        return glm::vec3(1,1,1); //Because light is white by default
    }


/***** OTHERS METHODS *****/

    void LightCubeInst::drawInstances(const Scene& scene, const ShadingProgram& prog, GLenum mode) const {
        glBindVertexArray(m_vao);
            glm::mat4 MVMatrix = scene.viewMatrix();

            //Send matrix to the CG
            glUniformMatrix4fv(prog.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(prog.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(scene.projMat() * MVMatrix));
            glUniformMatrix4fv(prog.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

            glDrawElementsInstanced(mode, nbIndexPerObj(), GL_UNSIGNED_INT, 0, nbInstances());

        glBindVertexArray(0);
    }

}