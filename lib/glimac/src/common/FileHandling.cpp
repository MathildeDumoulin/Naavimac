#include <iostream>
#include <fstream>
#include <glimac/common/FileHandling.hpp>
#include <glm/glm.hpp>
#include <algorithm>
#include <vector>

namespace glimac{
	
	void readFileCP(std::string fileName, std::vector<Controls> &controls){
		std::ifstream file("../assets/controlPoints/"+fileName, std::ios::in); 
		if(file)
		{
    		std::string line;
    		for( std::string line; getline(file, line);)
			{
			    Controls cp;
        		file >> cp.pos.x;
        		file >> cp.pos.y;
        		file >> cp.pos.z;
        		file >> cp.value;
        		std::cout << cp.pos.x << " " << cp.pos.y << " " << cp.pos.z << " value : " << cp.value << std::endl;
			}
			file.close();  
		}
		 else  
            std::cerr << "Unable to open the file" << std::endl; 
	}
	
}