#ifndef CUBE_EDGES_HPP__
#define CUBE_EDGES_HPP__
#pragma once

#include <vector>

#include "glimac/common/ShapeVertex.hpp"
#include "glimac/primitives/Primitive.hpp"

namespace glimac {

class CubeEdges : public Primitive<ShapeVertex> {
    public:
        CubeEdges();
        ~CubeEdges() = default;
};

}

#endif