#include <iostream>
#include <fstream>
#include <glimac/common/FileHandling.hpp>
#include <glm/glm.hpp>
#include <algorithm>
#include <vector>

namespace glimac{
	
	///Reading file containing control points for RBFs
	void readFileCP(std::string fileName, std::vector<Controls> &controls){
		std::ifstream file("../assets/controlPoints/"+fileName, std::ios::in); 
		if(file)
		{
    		std::string line;
    		while(getline(file, line))
			{
				Controls cp;
				std::stringstream coordValue(line);
				coordValue >> cp.pos.x;
				coordValue >> cp.pos.y;
				coordValue >> cp.pos.z;
				coordValue >> cp.weight;
				controls.push_back(cp);
        		
			}
			file.close();  
		}
		 else  
            std::cerr << "Unable to open the file" << std::endl; 
	}
	
}