#pragma once

#include <GL/glew.h>
#include <assert.h>
#include <iostream>

/**
 * @brief Assertion and logger handling for opengl functions
 */
#ifndef NDEBUG
    #define BreakAssert(x) if (!x) { assert(false); }
    #define GLCall(x) glexp::clear(); x; BreakAssert(glexp::doesFunctionWorks(#x, __FILE__, __LINE__))
#else
    #define GLCall(x) x
#endif

namespace glexp {
    /**
     * @brief Empty the OpenGl error buffer
     */
    void clear() {
        while (glGetError() != GL_NO_ERROR);
    }

    /**
     * @brief Transform error enum to text for OpenGL
     * 
     * @param err 
     * @return char const* - Text corresponding to OpenGl error
     */
    char const* glErrorString(GLenum const err) {
        switch (err) {
        case GL_NO_ERROR:
            return "GL_NO_ERROR";

        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";

        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";

        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";

        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";

        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";

        default:
            assert(!"unknown error");
            return nullptr;
        }
    }

    /**
     * @brief Print OpenGl errors to the console if any
     * 
     * @param functionName
     * @param filename
     * @param line
     */
    bool doesFunctionWorks(const char* functionName, const char* filename, int line) {
        GLenum error;
        while ((error = glGetError()) != GL_NO_ERROR) {
            std::cout << "[OpenGL Error] " << glErrorString(error) << " : " << functionName << " " << filename << " " << line << std::endl;
            return false;
        }
        return true;
    }
}