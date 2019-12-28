#include "glimac/common/Instance.hpp"
#include <GL/glew.h>

#include <glimac/common/Object.hpp>
#include <glimac/common/VertexArray.hpp>

#include "app/const.hpp"

#include <algorithm>

namespace glimac {

/***** CONSTRUCTORS & DESTRUCTOR *****/

    Instance::Instance(const unsigned int nbInstances, const Object& obj) 
        : m_buffer(0), m_offsetPosition(nbInstances), m_nbIndexPerObj(obj.nbIndex()), m_vao(POS_NORM_TEXT, obj) {

            //Avoid memory leak
            if(glIsBuffer(m_buffer) == GL_TRUE) glDeleteBuffers(1, &m_buffer);

            //Buffer Creation
            glGenBuffers(1, &m_buffer);

            const GLuint VERTEX_ATTR_OFFSET = 3;

            glBindVertexArray(m_vao.vao());
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.ibo());

                glEnableVertexAttribArray(VERTEX_ATTR_OFFSET);

                glBindBuffer(GL_ARRAY_BUFFER, m_buffer); 
                    glVertexAttribPointer(VERTEX_ATTR_OFFSET, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
                glBindBuffer(GL_ARRAY_BUFFER, 0); 
                glVertexAttribDivisor(VERTEX_ATTR_OFFSET, 1);
            glBindVertexArray(0);
    }

    Instance::~Instance() {
        glDeleteBuffers(1, &m_buffer);
    }


    void Instance::refresh() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_offsetPosition.size(), &m_offsetPosition[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

/***** GETTERS & SETTERS *****/

    const size_t Instance::nbInstances() const {
        return m_offsetPosition.size();
    }

    const GLsizei Instance::nbIndexPerObj() const {
        return m_nbIndexPerObj;
    }

    std::vector<glm::vec3>& Instance::offsetPosition() {
        return m_offsetPosition;
    }

    const VertexArray& Instance::vao() const {
        return m_vao;
    }

/***** OTHERS METHODS *****/

    bool Instance::isThereSomething(const glm::vec3& position) const {
        for(const auto &inst:m_offsetPosition) {
            if(position == inst) return true;
        }
        return false;
    }

    void Instance::addInstance(const glm::vec3& position) {
        if(!isThereSomething(position)) m_offsetPosition.push_back(position);
        refresh();
    }

    void Instance::removeInstance(const glm::vec3& position) {
        if(isThereSomething(position)) {
            m_offsetPosition.erase(std::remove(m_offsetPosition.begin(), m_offsetPosition.end(), position), m_offsetPosition.end());
        }
        refresh();
    }

    void Instance::drawInstances(const Scene& scene, const ShadingProgram& prog) const {
        m_vao.bindVAO();
            glm::mat4 MVMatrix = scene.viewMatrix();

            //Send matrix to the CG
            glUniformMatrix4fv(prog.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(prog.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(scene.projMat() * MVMatrix));
            glUniformMatrix4fv(prog.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

            glDrawElementsInstanced(GL_TRIANGLES, nbIndexPerObj(), GL_UNSIGNED_INT, 0, nbInstances());
        m_vao.unbindVAO();
    }

}