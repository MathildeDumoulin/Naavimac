#ifndef FILE_HPP 
#define FILE_HPP
#pragma once

#include <glimac/rbf/Rbf.hpp>
#include <glimac/common/glm.hpp>
#include <glimac/common/CubeList.hpp>
#include <iostream>
#include <vector>

namespace glimac {
	
	void readFileCP(std::string fileName, std::vector<Controls> &controls);
}

#endif