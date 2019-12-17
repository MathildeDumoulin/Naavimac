#include "glimac/common/VertexArray.hpp"
#include "glimac/common/ShapeVertex.hpp"

namespace glimac {

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_vao);
}

void VertexArray::addObject(const Object &obj) {
    glBindVertexArray(m_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.ibo());

        const GLuint VERTEX_ATTR_POSITION = 0;
        const GLuint VERTEX_ATTR_NORMAL = 1;
        const GLuint VERTEX_ATTR_TEXTURE = 2;
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

        glBindBuffer(GL_ARRAY_BUFFER, obj.vbo()); //Binding the VBO inside the VAO
            glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, position)));
            glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, normal)));
            glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, texCoords)));
        glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbinding the VBO
    glBindVertexArray(0); //Unbinding the VAO
}

const GLuint VertexArray::vao() const {
    return m_vao;
}

}