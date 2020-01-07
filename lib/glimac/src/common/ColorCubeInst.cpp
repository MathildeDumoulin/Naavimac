#include "glimac/common/ColorCubeInst.hpp"
#include <glimac/common/Image.hpp>
#include <iostream>
#include <GL/glew.h>

#include <glimac/common/Object.hpp>

#include "app/const.hpp"

#include <algorithm>

namespace glimac {

/***** CONSTRUCTORS & DESTRUCTOR *****/

    ColorCubeInst::ColorCubeInst(const unsigned int nbInstances, const Object& obj) 
        : Instance(nbInstances, obj), m_bufferColor(0), m_offsetColor(nbInstances) {

            //Avoid memory leak
            if(glIsBuffer(m_bufferColor) == GL_TRUE) glDeleteBuffers(1, &m_bufferColor);

            //Buffer Creation
            glGenBuffers(1, &m_bufferColor);

            const GLuint VERTEX_ATTR_COLOR = 4;

            glBindVertexArray(m_vao);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.ibo());

                glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

                glBindBuffer(GL_ARRAY_BUFFER, m_bufferColor); 
                    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
                glBindBuffer(GL_ARRAY_BUFFER, 0); 
                glVertexAttribDivisor(VERTEX_ATTR_COLOR, 1);
            glBindVertexArray(0);

            for(size_t i = 0; i < nbInstances; ++i) {
                m_offsetColor[i] = glm::vec3(1.f,1.f,1.f);
            }
            refresh();
        }

    ColorCubeInst::~ColorCubeInst() {
        glDeleteBuffers(1, &m_bufferColor);
        std::cout << "Deleting ColorCubeInst" << std::endl;
    }

    void ColorCubeInst::refresh() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferPosition);
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_offsetPosition.size(), &m_offsetPosition[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, m_bufferColor);
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_offsetColor.size(), &m_offsetColor[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

/***** PRIVATE METHODS *****/

    void ColorCubeInst::loadTextures(const std::string& diffuseFp) {
        //DO NOTHING
    }

/***** GETTERS & SETTERS *****/

    const glm::vec3 ColorCubeInst::getColor(const glm::vec3& position) const {
        //Find index corresponding to this position
        auto it = std::find(m_offsetPosition.cbegin(), m_offsetPosition.cend(), position);

        if(it != m_offsetPosition.cend()) {
            int index = distance(m_offsetPosition.cbegin(), it);

            return m_offsetColor[index];
        }
        return glm::vec3(0,0,0);
    }


/***** OTHERS METHODS *****/

    void ColorCubeInst::addInstance(const glm::vec3& position, const glm::vec3& color) {
        if(!isThereSomething(position)) {
            m_offsetPosition.push_back(position);
            m_offsetColor.push_back(color);

            refresh();
        }
    }

    void ColorCubeInst::removeInstance(const glm::vec3& position) {
        //Find index corresponding to this position
        auto it = std::find(m_offsetPosition.cbegin(), m_offsetPosition.cend(), position);

        if(it != m_offsetPosition.cend()) {
            int index = distance(m_offsetPosition.cbegin(), it);

            m_offsetPosition.erase(m_offsetPosition.begin() + index);
            m_offsetColor.erase(m_offsetColor.begin() + index);
            refresh();
        } 
    }

    void ColorCubeInst::drawInstances(const Scene& scene, const ShadingProgram& prog, GLenum mode) const {
        scene.lighting().sendLights(prog);

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