#ifndef UIWINDOWS_HPP__
#define UIWINDOWS_HPP__
#pragma once

#include <imgui/imgui.h>
#include <glimac/common/Scene.hpp>
#include <glimac/common/CubeList.hpp>
#include <glimac/common/ColorCubeInst.hpp>


namespace glimac{

	void cubesWindow(Scene &scene, CubeList &cubeList,const glm::vec3 &position, ColorCubeInst &cubeEdgesObj);
	void lightWindow(Scene &scene);

}

#endif