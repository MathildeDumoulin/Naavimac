#include <glimac/rbf/Rbf.hpp>
#include <iostream>
#include <math.h>

namespace glimac{
	double gaussian(glm::vec3 vec1, glm::vec3 vec2, const float epsilon){
		double d = glm::distance(vec1, vec2);
		return exp(-epsilon*d*d);
	}

	double multiquadric(glm::vec3 vec1, glm::vec3 vec2, const float epsilon){
		float d = glm::distance(vec1, vec2);
		return double(sqrt(1.0 + epsilon*d*epsilon*d));
	}

	double getNorm(const glm::vec3 vec){
    	return (double)sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
  	} 

  	//example, will be replaced later with custom rbfs
  	const double phi(const double &d){
    	return d;
	}

	void omega(std::vector <Controls> &controls){

		Eigen::MatrixXd constraint = Eigen::MatrixXd::Zero(controls.size(), controls.size());

		for(int i = 0; i < controls.size(); i++) {
			for(int j = 0; j < controls.size(); j++) {
				constraint(i, j) = phi(double(glm::distance(controls.at(i).pos, controls.at(j).pos)));
			}
		}

		Eigen::MatrixXd reverse = constraint.inverse();
		Eigen::VectorXd weights(controls.size());
		Eigen::VectorXd finalValues(controls.size());

		
		for (int i = 0; i < controls.size(); i++){
			weights(i) = controls.at(i).weight;
		}

		finalValues = reverse*weights;
		
		for(int i = 0; i < controls.size(); i++){
			controls.at(i).value = finalValues(i);
		}

		std::cout << finalValues << std::endl;

	}
	
};
	
