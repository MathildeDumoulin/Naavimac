#include "glimac/common/CubeList.hpp"
#include <GL/glew.h>

#include <glimac/common/Object.hpp>

#include "app/const.hpp"

#include <iostream>

namespace glimac {

/***** CONSTRUCTORS & DESTRUCTOR *****/

    CubeList::CubeList(const Object& obj) 
        : m_world((worldSizeX+1) * (worldSizeY+1) * (worldSizeZ+1)) {
            for(auto &elt:m_world) {
                elt = NONE;
            }

            m_instances.insert(std::make_pair(DIRT, std::make_shared<Instance>(nbCubesAtStart, obj)));
            m_instances.insert(std::make_pair(WATER, std::make_shared<Instance>(0, obj)));

            createStartCubesGround();
    }


/***** PRIVATE METHODS *****/

    const glm::vec3 CubeList::positionFromIndex(int index) const {
        assert(index < (worldSizeX+1)*(worldSizeY+1)*(worldSizeZ+1) && index >= 0);

        float x = index / ((worldSizeZ + 1) * (worldSizeY + 1)) + worldMinX;

        index = index % ((worldSizeZ + 1) * (worldSizeY + 1));

        float y = index / (worldSizeZ + 1) + worldMinY;
        float z = index % (worldSizeZ + 1) + worldMinZ;

        return glm::vec3(x, y, z);
    }

    const int CubeList::indexFromPosition(const glm::vec3& vec) const {
        assert(vec.x >= worldMinX && vec.x <= worldMaxX && 
                    vec.y >= worldMinY && vec.y <= worldMaxY && 
                        vec.z >= worldMinZ && vec.z <= worldMaxZ);

        int index = (vec.x - worldMinX) * (worldSizeZ + 1) * (worldSizeY + 1);
        index += (vec.y - worldMinY) * (worldSizeZ + 1);
        index += vec.z - worldMinZ;

        return index;
    }

    void CubeList::createStartCubesGround() {
        assert(m_instances.at(DIRT)->offsetPosition().size() == nbCubesAtStart);

        int count = 0;

        //Here, we cant use the "type()" method because of the push_back()/refresh()
        for(int y = -1; y <= 1; ++y) {
            for(int x = worldMinX; x <= worldMaxX; ++x) {
                for(int z = worldMinZ; z <= worldMaxZ; ++z) {
                    m_world[indexFromPosition(glm::vec3(x, y, z))] = DIRT; //Change type in the m_world vector
                    m_instances.at(DIRT)->offsetPosition().at(count) = glm::vec3(x, y, z); //Add position into the DIRT instance drawing vector
                    ++count;
                }
            }
        }

        m_instances.at(DIRT)->refresh(); //Send data to GPU
    }

/***** GETTERS & SETTERS *****/

    const CubeType CubeList::type(const glm::vec3& vec) const {
        if(vec.x >= worldMinX && vec.x <= worldMaxX && 
            vec.y >= worldMinY && vec.y <= worldMaxY && 
                vec.z >= worldMinZ && vec.z <= worldMaxZ) {
                    return m_world[indexFromPosition(vec)];
        }
        else {
            return NONE;
        }
    }

    void CubeList::type(const glm::vec3& vec, const CubeType& newType) {
        if(vec.x >= worldMinX && vec.x <= worldMaxX && 
            vec.y >= worldMinY && vec.y <= worldMaxY && 
                vec.z >= worldMinZ && vec.z <= worldMaxZ) {
                    int index = indexFromPosition(vec);

                    CubeType oldType = m_world[index];

                    if(oldType == newType) return;

                    m_world[index] = newType;

                    if(oldType != NONE) m_instances.at(oldType)->removeInstance(vec);
                    if(newType != NONE) m_instances.at(newType)->addInstance(vec);
        }
    }

    std::shared_ptr<Instance> CubeList::instance(const CubeType& type) {
        return m_instances.at(type);
    }

}