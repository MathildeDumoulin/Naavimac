#ifndef RBF_HPP 
#define RBF_HPP
#pragma once


#include <vector>
#include <math.h>
#include <numeric>
#include <algorithm>
#include <eigen3/Eigen/Dense>
#include "glimac/common/CubeList.hpp"

namespace glimac {

	//Class storing control points in the txt file
    class Controls
    {
    public:
        glm::vec3 pos;
        float weight; // will be set later using rbfs
        float value; // specified in txt file
    };

    ///Our different types of radial basis functions
    //Get result from chosen RBF
   	double gaussian(glm::vec3 vec1, glm::vec3 vec2, const float epsilon);
   	double multiquadric(glm::vec3 vec1, glm::vec3 vec2, const float epsilon);

   	//will display result depending on chosen RBF
   	double chooseRBF(int type); // 0 for gaussian, 1 for multiquadric

    ///get Omega for the current RBF
    const Eigen::VectorXd getOmega(const std::vector <Controls> &controls);

    ///applying our RBF to our scene 
    void applyRbf(CubeList &cubeList, const std::vector <Controls> &controls, int RbfType);
}

#endif