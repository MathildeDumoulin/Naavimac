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
#include <glimac/common/VertexArray.hpp>
#include <glimac/common/Instances.hpp>
#include <glimac/primitives/Cube.hpp>
#include <glimac/primitives/CubeEdges.hpp>
#include <glimac/cam/FreeflyCamera.hpp>
#include <iostream>
#include <vector>

#include <cmath>
#include "glimac/gui/Mouse.hpp"

#include "app/const.hpp"

#include "glimac/common/Scene.hpp"



using namespace glimac;


int main(int argc, char** argv) {
    // Initialize SDL & OpenGL + open a window
    const int WINDOW_WIDTH = 600;
    const int WINDOW_HEIGHT = 600;
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "GLImac");

    // Initialize ImGui
    IMGUIWindowManager interface(windowManager);

    Mouse mouse;

    Scene scene;


    //INITIALISATION

        //Load, compile and tell OpenGL to use these shaders
        FilePath applicationPath(argv[0]);
        ShadingProgram texturedCubeProgram(applicationPath, "texturedCube.vs.glsl", "texturedCube.fs.glsl");
        ShadingProgram smallCubeProgram(applicationPath, "smallCube.vs.glsl", "texturedCube.fs.glsl");
        ShadingProgram selectionCubeProgram(applicationPath, "selectionCube.vs.glsl", "selectionCube.fs.glsl");


    //CUBE
    Object cubeObj = Object(Cube()); //VBO and IBO
    VertexArray cube(POS_NORM_TEXT, cubeObj);

    Instances cubeList(nbCubesAtStart, cubeObj, cube); //Create instance of CubeObjects
    cubeList.createCubesGround();

    //CUBE EDGES
    Object cubeEdgesObj = Object(CubeEdges(0.05));
    VertexArray cubeEdges(POS, cubeEdgesObj);


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
                    if(e.key.keysym.sym == SDLK_UP) scene.selection().y++;
                    if(e.key.keysym.sym == SDLK_DOWN) scene.selection().y--;
                    if(e.key.keysym.sym == SDLK_LEFT) scene.selection().x--;
                    if(e.key.keysym.sym == SDLK_RIGHT) scene.selection().x++;
                    if(e.key.keysym.sym == SDLK_COMMA) scene.selection().z--;
                    if(e.key.keysym.sym == SDLK_SEMICOLON) scene.selection().z++;
                    if(e.key.keysym.sym == SDLK_SPACE) cubeList.addInstance(scene.selection());
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
                        cube.bindVAO();
                            smallCubeProgram.use();
                                cubeList.drawInstances(scene, smallCubeProgram);        
                        cube.unbindVAO();

                        //Update selection position
                        mouse.updateSelection(scene, cubeList);
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    mouse.leftDown(false);
                    mouse.rightDown(false);
                    break;

                case SDL_MOUSEMOTION:
                    if(mouse.leftDown()) {
                        glm::ivec2 offsetMouse = windowManager.getMousePosition() - mouse.position();
                        mouse.updatePosition(windowManager);
                        scene.cam().rotateUp(-offsetMouse.y/2.f);
                        scene.cam().rotateLeft(-offsetMouse.x/2.f);
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

        cube.bindVAO(); // Binding VAO
            texturedCubeProgram.use();
                cubeList.drawInstances(scene, texturedCubeProgram);        
        cube.unbindVAO();

        cubeEdges.bindVAO();
            selectionCubeProgram.use();
                glm::mat4 cubeMVMatrix = glm::translate(scene.viewMatrix(), scene.selection());
                cubeEdgesObj.draw(scene, selectionCubeProgram, cubeMVMatrix);
        cubeEdges.unbindVAO();

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}