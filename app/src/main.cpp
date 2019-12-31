#include "app/main.hpp"
#include <glimac/gui/SDLWindowManager.hpp>
#include <glimac/gui/IMGUIWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/shading/Program.hpp>
#include <glimac/shading/ShadingProgram.hpp>
#include <glimac/common/FilePath.hpp>
#include <glimac/common/glm.hpp>
#include <glimac/common/Image.hpp>
#include <glimac/common/Object.hpp>
#include <glimac/common/Instance.hpp>
#include <glimac/primitives/Cube.hpp>
#include <glimac/primitives/CubeEdges.hpp>
#include <glimac/cam/FreeflyCamera.hpp>
#include <iostream>
#include <vector>

#include <cmath>
#include "glimac/gui/Mouse.hpp"

#include "app/const.hpp"

#include "glimac/common/Scene.hpp"

#include "glimac/common/CubeList.hpp"



using namespace glimac;


int main(int argc, char** argv) {
    // Initialize SDL & OpenGL + open a window
    SDLWindowManager windowManager(windowWidth, windowHeight, "GLImac");

    // Initialize ImGui
    IMGUIWindowManager interface(windowManager);

    Mouse mouse;

    Scene scene;


    //INITIALISATION

        //Load, compile and tell OpenGL to use these shaders
        FilePath applicationPath(argv[0]);
        ShadingProgram texturedCubeProgram(applicationPath, "texturedCube.vs.glsl", "texturedCube.fs.glsl");
        ShadingProgram smallCubeProgram(applicationPath, "smallCube.vs.glsl", "texturedCube.fs.glsl");
        ShadingProgram selectionCubeProgram(applicationPath, "selectionCube.vs.glsl", "selectionCube.fs.glsl", "selectionCube.gs.glsl");


    //CUBE
    Object cubeObj = Object(Cube()); //VBO and IBO

    CubeList cubeList(cubeObj);


    //CUBE EDGES
    Object cubeEdgesObj = Object(CubeEdges());
    Instance cubeEdges(1, cubeEdgesObj);


    glEnable(GL_DEPTH_TEST);

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            interface.processEvent(e);
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            switch(e.type) {
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_z) scene.cam().moveFront(1);
                    if(e.key.keysym.sym == SDLK_s) scene.cam().moveFront(-1);
                    if(e.key.keysym.sym == SDLK_q) scene.cam().moveLeft(1);
                    if(e.key.keysym.sym == SDLK_d) scene.cam().moveLeft(-1);
                    if(e.key.keysym.sym == SDLK_a) scene.cam().moveUp(-1);
                    if(e.key.keysym.sym == SDLK_e) scene.cam().moveUp(1);
                    if(e.key.keysym.sym == SDLK_UP) scene.moveSelection(glm::vec3(0,1,0)); cubeEdges.changeFirstInstance(scene.selection());
                    if(e.key.keysym.sym == SDLK_DOWN) scene.moveSelection(glm::vec3(0,-1,0)); cubeEdges.changeFirstInstance(scene.selection());
                    if(e.key.keysym.sym == SDLK_LEFT) scene.moveSelection(glm::vec3(-1,0,0)); cubeEdges.changeFirstInstance(scene.selection());
                    if(e.key.keysym.sym == SDLK_RIGHT) scene.moveSelection(glm::vec3(1,0,0)); cubeEdges.changeFirstInstance(scene.selection());
                    if(e.key.keysym.sym == SDLK_COMMA) scene.moveSelection(glm::vec3(0,0,-1)); cubeEdges.changeFirstInstance(scene.selection());
                    if(e.key.keysym.sym == SDLK_SEMICOLON) scene.moveSelection(glm::vec3(0,0,1)); cubeEdges.changeFirstInstance(scene.selection());
                    if(e.key.keysym.sym == SDLK_SPACE) cubeList.type(scene.selection(), DIRT);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(e.button.button == SDL_BUTTON_LEFT) {
                        mouse.leftDown(true);
                        mouse.updatePosition(windowManager);
                    }
                    if(e.button.button == SDL_BUTTON_RIGHT) {
                        mouse.rightDown(true);
                        mouse.updatePosition(windowManager);

                        //Draw smaller cubes to make mouse selection easier
                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                            smallCubeProgram.use();
                                cubeList.instance(DIRT)->drawInstances(scene, texturedCubeProgram);        

                        //Update selection position
                        mouse.updateSelection(scene, cubeList);
                        cubeEdges.changeFirstInstance(scene.selection());
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    mouse.leftDown(false);
                    mouse.rightDown(false);
                    mouse.resetOffsetCounter();
                    break;

                case SDL_MOUSEMOTION:
                    if(mouse.leftDown()) {
                        glm::ivec2 offsetMouse = windowManager.getMousePosition() - mouse.position();
                        mouse.updatePosition(windowManager);
                        scene.cam().rotateUp(-offsetMouse.y/2.f);
                        scene.cam().rotateLeft(-offsetMouse.x/2.f);
                    }

                    if(mouse.rightDown()) {
                        mouse.updateSelectionMotion(scene, windowManager, cubeEdges);
                    }
                    break;
            }
        }

        /* IMGUI */

        // Start the Dear ImGui frame
        interface.startFrame(windowManager);

        {
            ImGui::Begin("Another Window");
            ImGui::Text("Hello from another window!");
            ImGui::End();
        }

        // Rendering
        interface.render();

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear window

        interface.draw();

        texturedCubeProgram.use();
            cubeList.instance(DIRT)->drawInstances(scene, texturedCubeProgram);        

        selectionCubeProgram.use();
            cubeEdges.drawInstances(scene, selectionCubeProgram, GL_LINES);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}