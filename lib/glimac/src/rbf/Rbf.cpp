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

	//double invQuadratic()

	double getNorm(const glm::vec3 vec){
    	return (double)sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
  	} 

  	//example, will be replaced later with custom rbfs
  	const double phi(const double &d, int type, float e){
  		float epsilon = e;
  		switch(type){
  			//multiquadric
  			case 1: 
	  			return double(sqrt(1+epsilon*epsilon*d*d));
  				break;
  			//gaussian
  			case 2:
				return double(exp(-epsilon*d*d));
				break;
			//linear
			default : 
				return d*epsilon; 
  		}
	}

  	double resultRBF(std::vector <Controls> &controls, glm::vec3 vec, int type, float epsilon){
  		double weight;
  		for(int i = 0; i < controls.size(); i++) {
  			weight += controls.at(i).weight*phi(double(glm::distance(vec, controls.at(i).pos)), type,epsilon);
		}
		return weight;
  	}

	void omega(std::vector <Controls> &controls, int type, float epsilon){

		Eigen::MatrixXd constraint = Eigen::MatrixXd::Zero(controls.size(), controls.size());
		//Filling constraint matrix
		for(int i = 0; i < controls.size(); i++) {
			for(int j = 0; j < controls.size(); j++) {
				constraint(i, j) = phi(double(glm::distance(controls.at(i).pos, controls.at(j).pos)), type, epsilon);
			}
		}

		Eigen::MatrixXd reverse = constraint.inverse();
		//vector containing all weights from control points 
		Eigen::VectorXd weights(controls.size());
		Eigen::VectorXd finalValues(controls.size());

		//Filling weights vector with our control points weights
		for (int i = 0; i < controls.size(); i++){
			weights(i) = controls.at(i).weight;
		}

		//computing omega values
		finalValues = reverse*weights;
		
		//assign each omega value to its control point's value attribute
		for(int i = 0; i < controls.size(); i++){
			controls.at(i).value = finalValues(i);
		}

		//std::cout << finalValues << std::endl;

	}
	
};
	
