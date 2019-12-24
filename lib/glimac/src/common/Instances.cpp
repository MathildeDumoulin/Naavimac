#include "glimac/common/Instances.hpp"
#include <GL/glew.h>

#include <glimac/common/Object.hpp>
#include <glimac/common/VertexArray.hpp>

#include "app/const.hpp"

namespace glimac {

Instances::Instances(const unsigned int nbInstances, const Object& obj, const VertexArray& vao) 
    : m_buffer(0), m_offset(nbInstances), m_nbIndexPerObj(obj.nbIndex()) {

        //Avoid memory leak
        if(glIsBuffer(m_buffer) == GL_TRUE) glDeleteBuffers(1, &m_buffer);

        //Buffer Creation
        glGenBuffers(1, &m_buffer);

        const GLuint VERTEX_ATTR_OFFSET = 3;

        glBindVertexArray(vao.vao());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.ibo());

            glEnableVertexAttribArray(VERTEX_ATTR_OFFSET);

            glBindBuffer(GL_ARRAY_BUFFER, m_buffer); 
                glVertexAttribPointer(VERTEX_ATTR_OFFSET, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0); 
            glVertexAttribDivisor(VERTEX_ATTR_OFFSET, 1);
        glBindVertexArray(0);
}

Instances::~Instances() {
    glDeleteBuffers(1, &m_buffer);
}


void Instances::createCubesGround() {
    assert(m_offset.size() == nbCubesAtStart);

    int count = 0;

    for(int y = -1; y <= 1; ++y) {
        for(int x = worldMinX; x <= worldMaxX; ++x) {
            for(int z = worldMinZ; z <= worldMaxZ; ++z) {
                m_offset[count] = glm::vec3(x, y, z);
                ++count;
            }
        }
    }

    assert(m_offset.size() == count);

    refresh();
}

void Instances::refresh() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_offset.size(), &m_offset[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const size_t Instances::nbInstances() const {
    return m_offset.size() + 1;
}

const GLsizei Instances::nbIndexPerObj() const {
    return m_nbIndexPerObj;
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

void Instances::drawInstances(const Scene& scene, const ShadingProgram& prog) const {
    glm::mat4 MVMatrix = scene.viewMatrix();

    //Send matrix to the CG
    glUniformMatrix4fv(prog.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(prog.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(scene.projMat() * MVMatrix));
    glUniformMatrix4fv(prog.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

    glDrawElementsInstanced(GL_TRIANGLES, nbIndexPerObj(), GL_UNSIGNED_INT, 0, nbInstances());
}

}