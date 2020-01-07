#ifndef UIWINDOWS_HPP__
#define UIWINDOWS_HPP__
#pragma once

#include "imgui/imgui.h"
#include "glimac/common/Scene.hpp"
#include "glimac/common/CubeList.hpp"
#include <glimac/primitives/CubeEdges.hpp>
#include <glimac/common/Object.hpp>

void cubesWindow(Scene &scene, CubeList &cubeList, Object &cubeEdgesObj);

#endif