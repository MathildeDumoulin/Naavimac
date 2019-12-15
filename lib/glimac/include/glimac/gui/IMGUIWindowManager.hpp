#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glimac/gui/SDLWindowManager.hpp>


namespace glimac {

class IMGUIWindowManager{
    private:
        ImVec4 m_clearColor;
        ImGuiIO* m_io;

    public:
        //Constructor & Destructor
        IMGUIWindowManager(SDLWindowManager& sdl, ImVec4 color = ImVec4(0.f, 0.f, 0.f, 1.00f));
        ~IMGUIWindowManager();

        //Getters & Setters
        const ImVec4& clearColor() const;
        const ImGuiIO& io() const;

        //ImGui functions
        bool processEvent(SDL_Event& e);
        void startFrame(SDLWindowManager& sdl) const;
        void render() const;
        void draw() const;

};

}