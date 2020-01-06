#ifndef RBF_HPP 
#define RBF_HPP
#pragma once


#include <vector>
#include <math.h>
#include <numeric>
#include <algorithm>
#include <eigen3/Eigen/Dense>
#include <glimac/common/glm.hpp>


namespace glimac {

	//Class storing control points in the txt file
    struct Controls
    {
        glm::vec3 pos;
        float weight; // will be set later using rbfs
        float value; // specified in txt file
    };

    ///Our different types of radial basis functions
    //Get result from chosen RBF
   	double gaussian(glm::vec3 vec1, glm::vec3 vec2, const float epsilon);

   	double multiquadric(glm::vec3 vec1, glm::vec3 vec2, const float epsilon);

    double getNorm(const glm::vec3 vec);

    double resultRBF(std::vector <Controls> &controls, glm::vec3 vec);

    const double phi(const double &x);

    void omega(std::vector <Controls> &controls);

}

#endif