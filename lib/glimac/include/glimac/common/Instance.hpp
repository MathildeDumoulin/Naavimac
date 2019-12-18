#ifndef INSTANCE_HPP__
#define INSTANCE_HPP__
#pragma once

#include <vector>
#include <glimac/common/Object.hpp>
#include <glimac/common/VertexArray.hpp>

namespace glimac {

class Instance {
    private:
        GLuint m_buffer;
        std::vector<glm::vec3> m_offset;
        Object* m_obj;
        VertexArray* m_vao;

        void fillOffset(const unsigned int &width, const unsigned int &length, const unsigned int &height);

    public:
        Instance(const unsigned int &width, const unsigned int &length, const unsigned int &height, const Object& obj, const VertexArray& vao);
        ~Instance();
        void refresh() const;

        const size_t nbInstances() const;
};

}

#endif