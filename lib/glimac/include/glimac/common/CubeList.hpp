#ifndef CUBE_LIST_HPP__
#define CUBE_LIST_HPP__
#pragma once

#include <vector>
#include <map>
#include <memory>
#include <app/const.hpp>
#include <glimac/common/Object.hpp>
#include <glimac/common/Instance.hpp>
#include <glimac/common/FileHandling.hpp>
#include <glimac/rbf/Rbf.hpp>
#include <glimac/common/Scene.hpp>


namespace glimac {

enum CubeType {
    NONE, DIRT, WATER, COLOR, LIGHT
};

class CubeList {
    private:
        std::vector<CubeType> m_world;
        std::map<CubeType, std::shared_ptr<Instance>> m_instances;

        const glm::vec3 positionFromIndex(unsigned int index) const;
        const unsigned int indexFromPosition(const glm::vec3& vec) const;

        void createStartCubesGround();

    public:
        CubeList(Scene &scene, const Object& obj, const std::string filename = "");
        ~CubeList() = default;

        void type(Scene& scene, const glm::vec3& position, const CubeType& newType, const glm::vec3& color = glm::vec3(1.f,1.f,1.f)); //Setter
        const CubeType type(const glm::vec3& position) const; //Getter
        void applyRBF(Scene &scene, std::string filename, int typeRBF = 0, float epsilon = 1.0);

        void extrude(Scene& scene, Instance& selectionInst);
        void dig(Scene& scene, Instance& selectionInst);

        std::shared_ptr<Instance> instance(const CubeType& type);
};  

}

#endif