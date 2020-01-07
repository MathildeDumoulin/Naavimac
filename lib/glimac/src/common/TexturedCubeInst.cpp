#include "glimac/common/TexturedCubeInst.hpp"
#include <glimac/common/Image.hpp>
#include <iostream>
#include <GL/glew.h>

#include <glimac/common/Object.hpp>

#include "app/const.hpp"

#include <algorithm>

namespace glimac {

/***** CONSTRUCTORS & DESTRUCTOR *****/

    TexturedCubeInst::TexturedCubeInst(const unsigned int nbInstances, const Object& obj, const std::string& diffuseFp) 
        : Instance(nbInstances, obj), m_diffuseTexture(0) {
            
            if(diffuseFp != "") loadTextures(diffuseFp);
    }

    TexturedCubeInst::~TexturedCubeInst() {
        glDeleteTextures(1, &m_diffuseTexture);
        std::cout << "Deleting TexturedCubeInst" << std::endl;
    }


/***** PRIVATE METHODS *****/


    void TexturedCubeInst::loadTextures(const std::string& diffuseFp) {
        //DIFFUSE TEXTURE
            //Image loading
            std::unique_ptr<Image> diffuseImg = loadImage(diffuseFp);
            if(!diffuseImg) {
                std::cerr << "ERROR during texture loading" << std::endl;
                exit(EXIT_FAILURE);
            }

            //Avoid memory leak
            if(glIsTexture(m_diffuseTexture) == GL_TRUE) glDeleteTextures(1, &m_diffuseTexture);

            glGenTextures(1, &m_diffuseTexture);

            glBindTexture(GL_TEXTURE_2D, m_diffuseTexture);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, diffuseImg->getWidth(), diffuseImg->getHeight(), 0, GL_RGBA, GL_FLOAT, diffuseImg->getPixels());
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);
    }


/***** OTHERS METHODS *****/


    void TexturedCubeInst::drawInstances(const Scene& scene, const ShadingProgram& prog, GLenum mode) const {
        glUniform1i(prog.uTexture, 0);
        scene.lighting().sendLights(prog);

        glBindVertexArray(m_vao);
            glm::mat4 MVMatrix = scene.viewMatrix();

            //Send matrix to the CG
            glUniformMatrix4fv(prog.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(prog.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(scene.projMat() * MVMatrix));
            glUniformMatrix4fv(prog.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_diffuseTexture);
                glDrawElementsInstanced(mode, nbIndexPerObj(), GL_UNSIGNED_INT, 0, nbInstances());
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_diffuseTexture);
        glBindVertexArray(0);
    }

}