#ifndef SDL_WINDOW_MANAGER_HPP__
#define SDL_WINDOW_MANAGER_HPP__
#pragma once

#include <cstdint>
#include "SDL2/SDL.h"
#include "glimac/common/glm.hpp"

namespace glimac {

class SDLWindowManager {
    private:
        SDL_Window *m_window;
        SDL_GLContext m_openglContext;

    public:
        //Constructor & Destructor
        SDLWindowManager(uint32_t width, uint32_t height, const char* title);
        ~SDLWindowManager();

        //Getters & Setters
        SDL_Window* window();
        SDL_GLContext& glContext();

        //SDL functions
        bool pollEvent(SDL_Event& e);
        bool isKeyPressed(SDL_Keycode key) const;
        bool isMouseButtonPressed(uint32_t button) const; //button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
        glm::ivec2 getMousePosition() const;
        void swapBuffers();
        float getTime() const; // Return the time in seconds
};

}

#endif