#include <glimac/rbf/Rbf.hpp>
#include <iostream>
#include <math.h>

namespace glimac{

	//exp(-pow(abs(x * m_growthSpeed.getValue()), m_power.getValue()));

	double gaussian(const double d, const float epsilon){
		return exp(pow(epsilon, d));
		//return exp(-epsilon*d*d);
	}

	double multiquadric(const double d, const float epsilon){
		return double(sqrt(1.0 + epsilon*d*epsilon*d));
	}

	double invQuadratic(const double d, const float epsilon){
		return double(1.0/(1.0+epsilon*epsilon*d*d));
	}

	double bump(const double d){
		if(d < 1 && d > -1){
			return exp(-1.0/(1-d*d));
		}
		else return 0;
	}

  	//example, will be replaced later with custom rbfs
  	double phi(const double &d, int type, float e){
  		float epsilon = e;
  		switch(type){
  			//multiquadric
  			case 1: 
	  			return multiquadric(d,e);
  				break;
  			//gaussian
  			case 2:
				return gaussian(d,e);
				break;
			case 3:
				return invQuadratic(d,e);
				break;
			case 4 :
				return bump(epsilon);
				break;
			default : 
				return d*epsilon; 
  		}
	}

  	double resultRBF(std::vector <Controls> &controls, glm::vec3 vec, int type, float epsilon, int negative){
  		double weight;
  		for(uint i = 0; i < controls.size(); ++i) {
  			if(negative == 0){
  				weight += controls.at(i).weight*phi(double(glm::distance(vec, controls.at(i).pos)), type,epsilon);
  			}else{
  				weight -= controls.at(i).weight*phi(double(glm::distance(vec, controls.at(i).pos)), type,epsilon);
  			}
		}
		return weight;
  	}

	void omega(std::vector <Controls> &controls, int type, float epsilon){

		
		Eigen::MatrixXf constraint(controls.size(), controls.size());

		for (uint i = 0; i < controls.size(); ++i) {
			for (uint j = 0; j < controls.size(); ++j) {
				constraint(i, j) = phi(double(glm::distance(controls.at(i).pos, controls.at(j).pos)), type, epsilon);
			}
		}
		Eigen::VectorXf weights(controls.size());
		Eigen::VectorXf finalValues(controls.size());

		//Filling weights vector with our control points weights
		for (uint i = 0; i < controls.size(); ++i){
			weights(i) = controls.at(i).weight;
		}

		finalValues = constraint.householderQr().solve(weights);

		for(uint i = 0; i < controls.size(); ++i){
			controls.at(i).value = finalValues(i);
		}
	}
	
};
	
