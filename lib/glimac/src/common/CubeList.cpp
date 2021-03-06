#include "glimac/common/CubeList.hpp"
#include "glimac/common/TexturedCubeInst.hpp"
#include "glimac/common/ColorCubeInst.hpp"
#include "glimac/common/LightCubeInst.hpp"
#include <GL/glew.h>

#include <glimac/common/Object.hpp>

#include "app/const.hpp"

#include <iostream>

namespace glimac {

/***** CONSTRUCTORS & DESTRUCTOR *****/

    CubeList::CubeList(Scene &scene, const Object& obj, const std::string filename) 
        : m_world((worldSizeX+1) * (worldSizeY+1) * (worldSizeZ+1), NONE) {

            m_instances.insert(std::make_pair(DIRT, std::make_shared<TexturedCubeInst>(nbCubesAtStart, obj, "./bin/assets/textures/diffuse_DIRT.png")));
            m_instances.insert(std::make_pair(WATER, std::make_shared<TexturedCubeInst>(0, obj, "./bin/assets/textures/diffuse_WATER.png")));
            m_instances.insert(std::make_pair(COLOR, std::make_shared<ColorCubeInst>(0, obj)));
            m_instances.insert(std::make_pair(LIGHT, std::make_shared<LightCubeInst>(0, obj)));

            
            if(filename != ""){
                applyRBF(scene, filename);
            }else{
                createStartCubesGround();
            }            
    }


/***** PRIVATE METHODS *****/

    const glm::vec3 CubeList::positionFromIndex(unsigned int index) const {
        assert(index < (worldSizeX+1)*(worldSizeY+1)*(worldSizeZ+1));

        float x = index / ((worldSizeZ + 1) * (worldSizeY + 1)) + worldMinX;

        index = index % ((worldSizeZ + 1) * (worldSizeY + 1));

        float y = index / (worldSizeZ + 1) + worldMinY;
        float z = index % (worldSizeZ + 1) + worldMinZ;

        return glm::vec3(x, y, z);
    }

    unsigned int CubeList::indexFromPosition(const glm::vec3& vec) const {
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
                    m_instances.at(DIRT)->offsetPosition().at(count) = glm::vec3(x, y, z); //Add position into the DIRT instance drawing vector (fill the vector)
                    ++count;
                }
            }
        }

        assert(count == nbCubesAtStart);

        m_instances.at(DIRT)->refresh(); //Send data to GPU
    }


    //Interpolation to generate the ground
    void CubeList::applyRBF(Scene &scene, const std::string filename, int typeRBF, float epsilon, int negative){
        std::vector <Controls> cpList;
        readFileCP(filename,cpList);
        //computing omega values to set weight for each cube later
        omega(cpList, typeRBF, epsilon);

        for(int y = -1; y <= 4; ++y){
            for(int x = worldMinX; x <= worldMaxX; ++x){
                for(int z = worldMinZ; z <= worldMaxZ; ++z){
                    glm::vec3 currentPos = glm::vec3(x, y, z);
                    //empty cube to refresh the scene
                    type(scene, currentPos, NONE);
                    double weight = resultRBF(cpList, currentPos, typeRBF, epsilon, negative);
                    if(weight >= 0){
                        type(scene, currentPos, DIRT);
                    }else{
                        //filling holes with water to create ocean / lakes
                        if(y<=0){
                            type(scene, currentPos, WATER);
                        }else{
                            type(scene, currentPos, NONE);
                        }
                        
                    }
                }
            }
        }
    }

    //generates water cubes to form an ocean
    void CubeList::FullOcean(Scene &scene){
        for(int y = -1; y <= 4; ++y){
            for(int x = worldMinX; x <= worldMaxX; ++x){
                for(int z = worldMinZ; z <= worldMaxZ; ++z){
                    glm::vec3 currentPos = glm::vec3(x, y, z);
                    if(y <= 0){
                        type(scene, currentPos, WATER);
                    }else{
                        type(scene, currentPos, NONE);
                    }
                }
            }
        }
    }

    //generates only dirt cubes 
    void CubeList::FullGround(Scene &scene){
        for(int y = -1; y <= 4; ++y){
            for(int x = worldMinX; x <= worldMaxX; ++x){
                for(int z = worldMinZ; z <= worldMaxZ; ++z){
                    glm::vec3 currentPos = glm::vec3(x, y, z);
                    type(scene, currentPos, DIRT);
                }
            }
        }
    }

/***** GETTERS & SETTERS *****/

    CubeType CubeList::type(const glm::vec3& position) const {
        //Check if the position is inside the world and return the index corresponding
        if(position.x >= worldMinX && position.x <= worldMaxX && 
            position.y >= worldMinY && position.y <= worldMaxY && 
                position.z >= worldMinZ && position.z <= worldMaxZ) {
                    return m_world[indexFromPosition(position)];
        }
        //If the position is outside the world, return NONE (important for the mouse selection)
        else {
            return NONE;
        }
    }

    void CubeList::type(Scene& scene, const glm::vec3& position, const CubeType& newType, const glm::vec3& color) {
        if(position.x >= worldMinX && position.x <= worldMaxX && 
            position.y >= worldMinY && position.y <= worldMaxY && 
                position.z >= worldMinZ && position.z <= worldMaxZ) {

                    int index = indexFromPosition(position);
                    CubeType oldType = m_world[index];
                    size_t nbLights = scene.lighting().nbLights();

                    if(newType == LIGHT && nbLights >= nbLightsMax) return;
                    if(oldType != COLOR && newType != COLOR && oldType == newType) return;

                    m_world[index] = newType;

                    if(oldType != NONE) m_instances.at(oldType)->removeInstance(position);
                    if(oldType == LIGHT) {
                        scene.changeLighting().removeLight(position);
                    }

                    if(newType == COLOR) {
                        m_instances.at(newType)->addInstance(position, color);
                        return;
                    }
                    if(newType != NONE) m_instances.at(newType)->addInstance(position);
                    if(newType == LIGHT) {
                        scene.changeLighting().addLight(position);
                    }
        }
    }

    void CubeList::extrude(Scene& scene, Instance& selectionInst) {
        glm::vec3 select = scene.selection();
        glm::vec3 normal = scene.faceAxis();
        CubeType cubeType = type(select);

        if(cubeType != NONE) {
            if(cubeType == COLOR) type(scene, select + normal, cubeType, m_instances.at(COLOR)->getColor(select));
            else type(scene, select + normal, cubeType); //Change the type of the adjacent cube
            scene.selection(select + normal); //Update the position of the selection
            selectionInst.changeFirstInstance(scene.selection()); //Update the GPU
        }
    }

    void CubeList::dig(Scene& scene, Instance& selectionInst) {
        glm::vec3 select = scene.selection();
        glm::vec3 normal = scene.faceAxis();

        type(scene, select, NONE); //Delete the current cube

        if(type(select - normal) != NONE) {
            scene.selection(select - normal); //Update the position of the selection
            selectionInst.changeFirstInstance(scene.selection()); //Update the GPU
        }
    }

    std::shared_ptr<Instance> CubeList::instance(const CubeType& type) {
        return m_instances.at(type);
    }

}