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
#include <glimac/primitives/Cube.hpp>
#include <glimac/cam/TrackballCamera.hpp>
#include <iostream>
#include <vector>


#define WORLD_WIDTH 5
#define WORLD_LENGTH 5
#define WORLD_HEIGHT 5

using namespace glimac;


int main(int argc, char** argv) {
    // Initialize SDL & OpenGL + open a window
    const int WINDOW_WIDTH = 600;
    const int WINDOW_HEIGHT = 600;
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "GLImac");

    // Initialize ImGui
    IMGUIWindowManager interface(windowManager);


    TrackballCamera cam;


    //INITIALISATION

        //Load, compile and tell OpenGL to use these shaders
        FilePath applicationPath(argv[0]);
        ShadingProgram mainProgram(applicationPath, "3D.vs.glsl", "3D.fs.glsl");
        ShadingProgram selectProgram(applicationPath, "3D.vs.glsl", "select.fs.glsl");


    //OBJECT
    Cube cube;
    Object myCube(cube.getVertexCount(), cube.getIndexCount(), cube.getVerticesPointer(), cube.getIndexesPointer());
    VertexArray vao;

    vao.addObject(myCube);


    glEnable(GL_DEPTH_TEST);


    /*
    std::vector<glm::vec3> cubes(WORLD_WIDTH * WORLD_LENGTH * 1);
    for(size_t i = 0; i < 1; ++i) {
        for(size_t j = 0; j < WORLD_WIDTH; ++j) {
            for(size_t k = 0; k < WORLD_LENGTH; ++k) {
                cubes[k+j*WORLD_LENGTH+i*WORLD_WIDTH*WORLD_LENGTH] = glm::vec3(j, i, k);
            }
        }
    }
    */

    std::vector<glm::vec3> cubes(5);
    for(size_t i = 0; i < 5; ++i) {
        cubes[i] = glm::vec3(i, 0, 0);
    }

    glm::vec3 selection(0.f, 0.f, 0.f);

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 600.f/600.f, 0.1f, 100.f);

    glm::ivec2 mouse;

    bool mouseDown = false;

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
                    if(e.key.keysym.sym == SDLK_UP) selection.y++;
                    if(e.key.keysym.sym == SDLK_DOWN) selection.y--;
                    if(e.key.keysym.sym == SDLK_LEFT) selection.x--;
                    if(e.key.keysym.sym == SDLK_RIGHT) selection.x++;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    mouseDown = true;
                    mouse = windowManager.getMousePosition();
                    break;

                case SDL_MOUSEBUTTONUP:
                    mouseDown = false;
                    break;

                case SDL_MOUSEMOTION:
                    if(mouseDown) {
                        glm::ivec2 offsetMouse = windowManager.getMousePosition() - mouse;
                        mouse = windowManager.getMousePosition();
                        cam.rotateUp(offsetMouse.y/2.f);
                        cam.rotateLeft(offsetMouse.x/2.f);
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

        glm::mat4 viewMatrix = cam.getViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear window

        interface.draw();

        glBindVertexArray(vao.vao()); // Binding VAO

            mainProgram.use();

                for(const auto &pos:cubes) {
                    //Make the cube rotate
                    // glm::mat4 cubeMVMatrix = glm::rotate(viewMatrix, windowManager.getTime(), glm::vec3(0, 1, 0));
                    glm::mat4 cubeMVMatrix = glm::translate(viewMatrix, pos);

                    //Send matrix to the CG
                    glUniformMatrix4fv(mainProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(cubeMVMatrix));
                    glUniformMatrix4fv(mainProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * cubeMVMatrix));
                    glUniformMatrix4fv(mainProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(cubeMVMatrix))));

                    glDrawElements(GL_TRIANGLES, cube.getIndexCount(), GL_UNSIGNED_INT, 0); //cube
                }

            selectProgram.use();

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                //Make the cube rotate
                // glm::mat4 cubeMVMatrix = glm::rotate(viewMatrix, windowManager.getTime(), glm::vec3(0, 1, 0));
                glm::mat4 cubeMVMatrix = glm::translate(viewMatrix, selection);
                cubeMVMatrix = glm::scale(cubeMVMatrix, glm::vec3(1.01, 1.01, 1.01));

                //Send matrix to the CG
                glUniformMatrix4fv(selectProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(cubeMVMatrix));
                glUniformMatrix4fv(selectProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * cubeMVMatrix));
                glUniformMatrix4fv(selectProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(cubeMVMatrix))));

                glDrawElements(GL_TRIANGLES, cube.getIndexCount(), GL_UNSIGNED_INT, 0); //cube

                glDisable(GL_BLEND);

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}