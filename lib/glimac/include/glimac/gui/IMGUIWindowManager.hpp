#ifndef IMGUI_WINDOW_MANAGER_HPP__
#define IMGUI_WINDOW_MANAGER_HPP__
#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glimac/common/glm.hpp>
#include <glimac/common/CubeList.hpp>
#include <glimac/gui/SDLWindowManager.hpp>


namespace glimac {

class IMGUIWindowManager{
    private:
        ImVec4 m_clearColor;
        ImGuiIO* m_io;

    public:
        //Constructor & Destructor
        IMGUIWindowManager(SDLWindowManager& sdl, ImVec4 color = ImVec4(0.7f, 0.7f, 0.7f, 1.00f));
        ~IMGUIWindowManager();

        //Getters & Setters
        const ImVec4& clearColor() const;
        const ImGuiIO& io() const;

        //setter for color
        void clearColor(const ImVec4 &vec);

        //ImGui functions
        bool processEvent(SDL_Event& e);
        void startFrame(SDLWindowManager& sdl) const;
        //void cubesWindow(Scene& scene, const glm::vec3& position, const glm::vec3& color = glm::vec3(1.f,0.f,0.f));
        void render() const;
        void draw() const;

};

}

#endif