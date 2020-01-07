#include "glimac/shading/ShadingProgram.hpp"

namespace glimac {

ShadingProgram::ShadingProgram(const FilePath& applicationPath, const char* vs, const char* fs, const char* gs)
    : m_Program(loadProgram(applicationPath.dirPath() + "shaders/" + vs, applicationPath.dirPath() + "shaders/" + fs, applicationPath.dirPath() + "shaders/" + gs)) {
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");

        uSunLightDir = glGetUniformLocation(m_Program.getGLId(), "uSunLightDir");
        uSunLightInt = glGetUniformLocation(m_Program.getGLId(), "uSunLightInt");
        uPointLightsInt = glGetUniformLocation(m_Program.getGLId(), "uPointLightsInt");
        uPointLights = glGetUniformLocation(m_Program.getGLId(), "uPointLights");
        uNbLight = glGetUniformLocation(m_Program.getGLId(), "uNbLight");
}

void ShadingProgram::use() const {
    m_Program.use();
}

}