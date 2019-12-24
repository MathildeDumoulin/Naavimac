#ifndef CUBE_HPP__
#define CUBE_HPP__
#pragma once

#include <vector>

#include "glimac/common/ShapeVertex.hpp"
#include "glimac/primitives/Primitive.hpp"

namespace glimac {

class Cube : public Primitive<ShapeVertex> {
    private:
        void pushQuad(const std::vector<ShapeVertexHomo> &quad);
    
    public:
        Cube();
};

}

#endif