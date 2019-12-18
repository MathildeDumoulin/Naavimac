#include "glimac/shading/ShadingProgram.hpp"

namespace glimac {

ShadingProgram::ShadingProgram(const FilePath& applicationPath, const char* vs, const char* fs)
    : m_Program(loadProgram(applicationPath.dirPath() + "shaders/" + vs, applicationPath.dirPath() + "shaders/" + fs)) {
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
}

void ShadingProgram::use() const {
    m_Program.use();
}

}