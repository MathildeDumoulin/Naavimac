#include "glimac/gui/SDLWindowManager.hpp"
#include <iostream>
#include <GL/glew.h>

namespace glimac {

/***** CONSTRUCTOR & DESTRUCTOR *****/

    SDLWindowManager::SDLWindowManager(uint32_t width, uint32_t height, const char* title) {
        // Initialize SDL window
        if(0 != SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << SDL_GetError() << std::endl;
            return;
        }

        // Use OpenGL 3.3
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
        SDL_GL_LoadLibrary(NULL);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        // Various attributes
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);	

        m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);

        if(!m_window) {
            std::cerr << SDL_GetError() << std::endl;
            return;
        }

        // Create OpenGL Context
        m_openglContext = SDL_GL_CreateContext(m_window);

        SDL_GL_MakeCurrent(m_window, m_openglContext);
        SDL_GL_SetSwapInterval(1); // Enable vsync

        // Initialize glew for OpenGL3+ support
        GLenum glewInitError = glewInit();
        if(GLEW_OK != glewInitError) {
            std::cerr << glewGetErrorString(glewInitError) << std::endl;
            return;
        }

        std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
    }

    SDLWindowManager::~SDLWindowManager() {
        SDL_GL_DeleteContext(m_openglContext);
        SDL_DestroyWindow(m_window);
        SDL_Quit();

        std::cout << "Fenetre SDL et contexte OpenGL détruits !" << std::endl;
    }


/***** GETTERS & SETTERS *****/

	SDL_Window* SDLWindowManager::window() {
		return m_window;
	}

	SDL_GLContext& SDLWindowManager::glContext() {
		return m_openglContext;
	}


/***** SDL FUNCTIONS *****/

	bool SDLWindowManager::pollEvent(SDL_Event& e) {
		return SDL_PollEvent(&e);
	}

	bool SDLWindowManager::isKeyPressed(SDL_Keycode key) const {
		return SDL_GetKeyboardState(nullptr)[key];
	}

	// button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
	bool SDLWindowManager::isMouseButtonPressed(uint32_t button) const {
		return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button);
	}

	glm::ivec2 SDLWindowManager::getMousePosition() const {
		glm::ivec2 mousePos;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		return mousePos;
	}

	void SDLWindowManager::swapBuffers() {
		SDL_GL_SwapWindow(m_window);
	}

	float SDLWindowManager::getTime() const {
		return 0.001f * SDL_GetTicks();
	}

}