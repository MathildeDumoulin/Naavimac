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

    GLuint uSunLightDir;
    GLuint uSunLightInt;
    GLuint uPointLightsInt;
    GLuint uPointLights;
    GLuint uNbLight;

    ShadingProgram(const FilePath& applicationPath, const char* vs, const char* fs, const char* gs = "");
    void use() const;
};

}

#endif