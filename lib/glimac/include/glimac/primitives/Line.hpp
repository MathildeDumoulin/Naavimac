#ifndef LINE_HPP__
#define LINE_HPP__
#pragma once

#include <vector>

#include "glimac/common/ShapeVertex.hpp"
#include "glimac/primitives/Primitive.hpp"
#include <GL/glew.h>

namespace glimac {

class Line : public Primitive<ShapeVertexHomo> {
    private:
        void pushQuad(const std::vector<ShapeVertexHomo> &quad);
    
    public:
        Line(const float& length, const float& thickness);

        void transform(const glm::mat4& mat);
};

}

#endif