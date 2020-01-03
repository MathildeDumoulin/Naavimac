#ifndef CUBE_LIST_HPP__
#define CUBE_LIST_HPP__
#pragma once

#include <vector>
#include <map>
#include <memory>
#include <app/const.hpp>
#include <glimac/common/Object.hpp>
#include <glimac/common/Instance.hpp>

namespace glimac {

enum CubeType {
    NONE, DIRT, WATER
};

class CubeList {
    private:
        std::vector<CubeType> m_world;
        std::map<CubeType, std::shared_ptr<Instance>> m_instances;

        const glm::vec3 positionFromIndex(unsigned int index) const;
        const unsigned int indexFromPosition(const glm::vec3& vec) const;

        void createStartCubesGround();

    public:
        CubeList(const Object& obj);
        ~CubeList() = default;

        void type(const glm::vec3& vec, const CubeType& newType); //Setter
        const CubeType type(const glm::vec3& vec) const; //Getter

        void extrude(Scene& scene, Instance& selectionInst);
        void dig(Scene& scene, Instance& selectionInst);

        std::shared_ptr<Instance> instance(const CubeType& type);
};  

}

#endif