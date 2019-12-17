#include "glimac/shading/ShadingProgram.hpp"

namespace glimac {

ShadingProgram::ShadingProgram(const FilePath& applicationPath)
    : m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl", applicationPath.dirPath() + "shaders/3D.fs.glsl")) {
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
}

void ShadingProgram::use() const {
    m_Program.use();
}

}