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

  	const double phi(const double &d){
    	return exp(-0.2*d*d);
	}

	const Eigen::VectorXd getOmega(const std::vector <Controls> &controls){
		
		//filling our constraint matrix
		Eigen::MatrixXd M_cons = Eigen::MatrixXd::Zero(controls.size(), controls.size());
	    for(unsigned int i = 0; i < controls.size(); i++){
	        for(unsigned int j = 0; j< controls.size(); j++){
	        //phi may be missing here
	          M_cons(i,j) = phi(getNorm(controls.at(i).pos-controls.at(j).pos));
	        }
	    }
	    
	    //filling vector with control points from the txt file
	    Eigen::VectorXd V_weight = Eigen::VectorXd::Ones(controls.size());
	    for(unsigned int i = 0; i < controls.size(); ++i){
	        V_weight[i]=controls.at(i).weight;
	    }

	    //Resolving system to find omega's value
	    Eigen::PartialPivLU<Eigen::MatrixXd> lu(M_cons);
	    Eigen::VectorXd omega = lu.solve(V_weight);

	    return omega;
	}

	//maybe return a vector here 
	void generateTerrain(CubeList cubeList, const std::vector <Controls> &controls){
		Eigen::VectorXd omega = getOmega(controls);
		float weight = 0.0;

		//loop with cubes + control points
	}
	
};
	
