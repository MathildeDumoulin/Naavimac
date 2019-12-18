#ifndef SHADING_PROGRAM_HPP__
#define SHADING_PROGRAM_HPP__
#pragma once

#include "glimac/shading/Program.hpp"

namespace glimac {

struct ShadingProgram {
    Program m_Program;

    GLuint uMVMatrix;
    GLuint uMVPMatrix;
    GLuint uNormalMatrix;
    GLuint uTexture;

    ShadingProgram(const FilePath& applicationPath, const char* vs, const char* fs);
    void use() const;
};

}

#endif