#include "glimac/common/Instance.hpp"
#include <glimac/common/Image.hpp>
#include <iostream>
#include <GL/glew.h>

#include <glimac/common/Object.hpp>

#include "app/const.hpp"

#include <algorithm>

namespace glimac {

/***** CONSTRUCTORS & DESTRUCTOR *****/

    Instance::Instance(const unsigned int nbInstances, const Object& obj) 
        : m_vao(0), m_bufferPosition(0), m_offsetPosition(nbInstances), m_nbIndexPerObj(obj.nbIndex()) {

            generateVertexArray(obj);

            //Avoid memory leak
            if(glIsBuffer(m_bufferPosition) == GL_TRUE) glDeleteBuffers(1, &m_bufferPosition);

            //Buffer Creation
            glGenBuffers(1, &m_bufferPosition);

            const GLuint VERTEX_ATTR_OFFSET = 3;

            glBindVertexArray(m_vao);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.ibo());

                glEnableVertexAttribArray(VERTEX_ATTR_OFFSET);

                glBindBuffer(GL_ARRAY_BUFFER, m_bufferPosition); 
                    glVertexAttribPointer(VERTEX_ATTR_OFFSET, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
                glBindBuffer(GL_ARRAY_BUFFER, 0); 
                glVertexAttribDivisor(VERTEX_ATTR_OFFSET, 1);
            glBindVertexArray(0);

            for(size_t i = 0; i < nbInstances; ++i) {
                m_offsetPosition[i] = glm::vec3(0,0,0);
            }
            refresh();
    }

    Instance::~Instance() {
        glDeleteBuffers(1, &m_bufferPosition);
        glDeleteVertexArrays(1, &m_vao);
        std::cout << "Deleting Instance" << std::endl;
    }


    void Instance::refresh() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferPosition);
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_offsetPosition.size(), &m_offsetPosition[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

/***** PRIVATE METHODS *****/

    void Instance::generateVertexArray(const Object& obj) {
        //Avoid memory leak
        if(glIsVertexArray(m_vao) == GL_TRUE) glDeleteVertexArrays(1, &m_vao);

        //VAO Creation
        glGenVertexArrays(1, &m_vao);

        const GLuint VERTEX_ATTR_POSITION = 0;
        const GLuint VERTEX_ATTR_NORMAL = 1;
        const GLuint VERTEX_ATTR_TEXTURE = 2;

        glBindVertexArray(m_vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.ibo());
            glBindBuffer(GL_ARRAY_BUFFER, obj.vbo());

                    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
                    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, position)));

                    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
                    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, normal)));

                    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
                    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, texCoords)));

            glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);
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

    const glm::vec3 Instance::getColor(const glm::vec3& position) const {
        return glm::vec3(0,0,0); //DO NOTHING BECAUSE NO COLOR DATA
    }

/***** OTHERS METHODS *****/

    void Instance::addInstance(const glm::vec3& position, const glm::vec3& color) {
        //Color is not used in this Class by default so we do not use it
        if(!isThereSomething(position)) m_offsetPosition.push_back(position);
        refresh();
    }

    void Instance::removeInstance(const glm::vec3& position) {
        if(isThereSomething(position)) {
            m_offsetPosition.erase(std::remove(m_offsetPosition.begin(), m_offsetPosition.end(), position), m_offsetPosition.end());
        }
        refresh();
    }

    bool Instance::isThereSomething(const glm::vec3& position) const {
        for(const auto &inst:m_offsetPosition) {
            if(position == inst) return true;
        }
        return false;
    }

    void Instance::changeFirstInstance(const glm::vec3& position) {
        m_offsetPosition[0] = position;
        refresh();
    }  

}