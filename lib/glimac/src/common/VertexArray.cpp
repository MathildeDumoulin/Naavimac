#include "glimac/common/VertexArray.hpp"
#include "glimac/common/ShapeVertex.hpp"

namespace glimac {

VertexArray::VertexArray(const ShaderAttrib& attrib, const Object& obj) : m_vao(0) {

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

            if(attrib >= POS) {
                glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
                glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, position)));
            }
            if(attrib >= POS_NORM) {
                glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
                glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, normal)));
            }
            if(attrib >= POS_NORM_TEXT) {
                glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
                glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, texCoords)));
            }

        glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_vao);
}

const GLuint VertexArray::vao() const {
    return m_vao;
}

void VertexArray::bindVAO() const {
    glBindVertexArray(m_vao);
}
void VertexArray::unbindVAO() const {
    glBindVertexArray(0);
}

}