#include "glimac/common/Instances.hpp"
#include <GL/glew.h>

#include <glimac/common/Object.hpp>
#include <glimac/common/VertexArray.hpp>

namespace glimac {

Instances::Instances(const unsigned int &width, const unsigned int &length, const unsigned int &height, const Object& obj, const VertexArray& vao) 
    : m_offset(width*length*height) {

        glGenBuffers(1, &m_buffer);
        fillOffset(width, length, height);

        refresh(); // Update the buffer

        //Bind the buffer in the VAO
        glBindVertexArray(vao.vao());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.ibo());

            const GLuint VERTEX_ATTR_OFFSET = 3;
            glEnableVertexAttribArray(VERTEX_ATTR_OFFSET);

            glBindBuffer(GL_ARRAY_BUFFER, m_buffer); //Binding the VBO inside the VAO
                glVertexAttribPointer(VERTEX_ATTR_OFFSET, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbinding the VBO
            glVertexAttribDivisor(VERTEX_ATTR_OFFSET, 1);
        glBindVertexArray(0); //Unbinding the VAO

}


void Instances::fillOffset(const unsigned int &width, const unsigned int &length, const unsigned int &height) {
    assert(m_offset.size() == width * length * height);

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            for(int k = 0; k < length; ++k) {
                m_offset[k + j*length + i*width*length] = glm::vec3(j, i, -k);
            }
        }
    }
}

void Instances::refresh() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_offset.size(), &m_offset[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const size_t Instances::nbInstances() const {
    return m_offset.size() + 1;
}

bool Instances::isThereSomething(const glm::vec3& position) const {
    for(const auto &inst:m_offset) {
        if(position == inst) return true;
    }
    return false;
}

void Instances::addInstance(const glm::vec3& position) {
    if(!isThereSomething(position)) m_offset.push_back(position);
    refresh();
}

}