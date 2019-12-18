#include "glimac/common/Instance.hpp"
#include <GL/glew.h>

#include <glimac/common/Object.hpp>
#include <glimac/common/VertexArray.hpp>

namespace glimac {

Instance::Instance(const unsigned int &width, const unsigned int &length, const unsigned int &height, const Object& obj, const VertexArray& vao) 
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

void Instance::fillOffset(const unsigned int &width, const unsigned int &length, const unsigned int &height) {
    assert(m_offset.size() == width * length * height);

    for(size_t i = 0; i < height; ++i) {
        for(size_t j = 0; j < width; ++j) {
            for(size_t k = 0; k < length; ++k) {
                m_offset[k + j*length + i*width*length] = glm::vec3(j, i, k);
            }
        }
    }
}

void Instance::refresh() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_offset.size(), &m_offset[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const size_t Instance::nbInstances() const {
    return m_offset.size() + 1;
}

}