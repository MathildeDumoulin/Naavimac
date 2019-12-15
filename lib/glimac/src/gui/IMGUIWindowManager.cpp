#include <glimac/gui/IMGUIWindowManager.hpp>
#include <iostream>
#include <GL/glew.h>

namespace glimac {

/***** CONSTRUCTOR & DESTRUCTOR *****/

    IMGUIWindowManager::IMGUIWindowManager(SDLWindowManager& sdl, ImVec4 color) : m_clearColor(color) {
        const char* glslVersion = "#version 330";

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        m_io = new ImGuiIO();
        *m_io = ImGui::GetIO();
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer bindings
        ImGui_ImplSDL2_InitForOpenGL(sdl.window(), sdl.glContext());
        ImGui_ImplOpenGL3_Init(glslVersion);
    }

    IMGUIWindowManager::~IMGUIWindowManager() {
        delete m_io;

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        std::cout << "Interface détruite !" << std::endl;
    }


/***** GETTERS & SETTERS *****/

    const ImVec4& IMGUIWindowManager::clearColor() const {
        return m_clearColor;
    }
    const ImGuiIO& IMGUIWindowManager::io() const {
        return *m_io;
    }


/***** IMGUI FUNCTIONS *****/

    bool IMGUIWindowManager::processEvent(SDL_Event& e) {
        return ImGui_ImplSDL2_ProcessEvent(&e);
    }

    void IMGUIWindowManager::startFrame(SDLWindowManager& sdl) const {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(sdl.window());
        ImGui::NewFrame();
    }

    void IMGUIWindowManager::render() const {
        ImGui::Render();
        glViewport(0, 0, (int)m_io->DisplaySize.x, (int)m_io->DisplaySize.y);
        glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
    }

    void IMGUIWindowManager::draw() const {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}