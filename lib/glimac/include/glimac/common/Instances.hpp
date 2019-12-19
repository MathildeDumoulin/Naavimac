#ifndef INSTANCE_HPP__
#define INSTANCE_HPP__
#pragma once

#include <vector>
#include <glimac/common/Object.hpp>
#include <glimac/common/VertexArray.hpp>

namespace glimac {


// Utiliser les stratégies pour modifier le vector m_offset en fonction du type de cube (et intégrer le changement de texture dans la statégie)
// Comme ça, on appelle le changement de stratégie, on refresh la liste des instances et on dessine les cubes avec la bonne texture !!
class Instances {
    private:
        GLuint m_buffer;
        std::vector<glm::vec3> m_offset;

        void fillOffset(const unsigned int &width, const unsigned int &length, const unsigned int &height);

    public:
        Instances(const unsigned int &width, const unsigned int &length, const unsigned int &height, const Object& obj, const VertexArray& vao);
        void refresh() const;

        const size_t nbInstances() const;
};

}

#endif