#include <glimac/rbf/Rbf.hpp>
#include <iostream>
#include <math.h>

namespace glimac{
	double gaussian(glm::vec3 vec1, glm::vec3 vec2, const float epsilon){
		float d = glm::distance(vec1, vec2);
		return exp(-epsilon*d*d);
	}

	double multiquadric(glm::vec3 vec1, glm::vec3 vec2, const float epsilon){
		float d = glm::distance(vec1, vec2);
		return float(sqrt(1.0 + epsilon*d*epsilon*d));
	}

	double getNorm(const glm::vec3 vec){
    	return (double)sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
  	} 

  	//example, will be replaced later with custom rbfs
  	const double phi(const double &x){
    	return exp(-0.3*x*x);
	}

	const Eigen::VectorXd getOmega(const std::vector <Controls> &controls){
		
		//generating constraint matrix
		Eigen::MatrixXd M_cons = Eigen::MatrixXd::Zero(controls.size(), controls.size());
	    for(int i = 0; i < controls.size(); i++){
	        for(int j = 0; j< controls.size(); j++){
	          //filling our first matrix with phi results
	        	M_cons(i,j) = phi(getNorm(controls.at(i).pos-controls.at(j).pos));
	          //M_cons(i,j) = phi(double(glm::distance(controls.at(i).pos - controls.at(j).pos)));
	        }
	    }
	    
	    //filling vector with control points from the txt file
	    Eigen::VectorXd V_weight = Eigen::VectorXd::Ones(controls.size());
	    for(unsigned int i = 0; i < controls.size(); ++i){
	        V_weight[i]=controls.at(i).weight;
	    }

	    //Finding all omega's value
	    Eigen::PartialPivLU<Eigen::MatrixXd> lu(M_cons);
	    Eigen::VectorXd omega = lu.solve(V_weight);
	    return omega;
	}
	
};
	
