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
        float weight; // specified in txt file
        float value; // will be set later with omega coeffs
    };

   
    double gaussian(const double d, const float epsilon);

   	double multiquadric(const double d, const float epsilon);

    double invQuadratic(const double d, const float epsilon);

    double resultRBF(std::vector <Controls> &controls, glm::vec3 vec, int type, float epsilon, int negative = 0);

    double phi(const double &x, int type, float e);

    void omega(std::vector <Controls> &controls, int type, float epsilon);

}

#endif