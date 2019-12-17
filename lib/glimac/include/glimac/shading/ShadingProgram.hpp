#ifndef SHADING_PROGRAM__
#define SHADING_PROGRAM__
#pragma once

#include "glimac/shading/Program.hpp"

namespace glimac {

struct ShadingProgram {
    Program m_Program;

    GLuint uMVMatrix;
    GLuint uMVPMatrix;
    GLuint uNormalMatrix;
    GLuint uTexture;

    ShadingProgram(const FilePath& applicationPath);
    void use() const;
};

}

#endif