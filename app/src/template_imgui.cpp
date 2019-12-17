#define DONTREAD
#ifndef DONTREAD


#include "app/main.hpp"
#include <glimac/gui/SDLWindowManager.hpp>
#include <glimac/gui/IMGUIWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/shading/Program.hpp>
#include <glimac/shading/ShadingProgram.hpp>
#include <glimac/common/FilePath.hpp>
#include <glimac/common/glm.hpp>
#include <glimac/common/Image.hpp>
#include <glimac/primitives/Cube.hpp>
#include <glimac/cam/TrackballCamera.hpp>
#include <iostream>
#include <vector>

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
        ShadingProgram mainProgram(applicationPath);


    //OBJECT
        Cube myCube;

        GLuint vbo;
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, myCube.getVertexCount() * sizeof(ShapeVertex), myCube.getVerticesPointer(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);


        GLuint ibo;
        glGenBuffers(1, &ibo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, myCube.getIndexCount() * sizeof(uint32_t), myCube.getIndexesPointer(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


        GLuint vao;
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); 

            const GLuint VERTEX_ATTR_POSITION = 0;
            const GLuint VERTEX_ATTR_NORMAL = 1;
            const GLuint VERTEX_ATTR_TEXTURE = 2;
            glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
            glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
            glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

            glBindBuffer(GL_ARRAY_BUFFER, vbo); //Binding the VBO inside the VAO
                glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, position)));
                glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, normal)));
                glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, texCoords)));
            glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbinding the VBO
        glBindVertexArray(0); //Unbinding the VAO


    glEnable(GL_DEPTH_TEST);


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
                    if(e.key.keysym.sym == SDLK_UP) cam.rotateUp(1);
                    if(e.key.keysym.sym == SDLK_DOWN) cam.rotateUp(-1);
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

        glBindVertexArray(vao); // Binding VAO

            mainProgram.use();

                //Make the cube rotate
                // glm::mat4 cubeMVMatrix = glm::rotate(viewMatrix, windowManager.getTime(), glm::vec3(0, 1, 0));
                glm::mat4 cubeMVMatrix = viewMatrix;

                //Send matrix to the CG
                glUniformMatrix4fv(mainProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(cubeMVMatrix));
                glUniformMatrix4fv(mainProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * cubeMVMatrix));
                glUniformMatrix4fv(mainProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(cubeMVMatrix))));

                glDrawElements(GL_TRIANGLES, myCube.getIndexCount(), GL_UNSIGNED_INT, 0); //cube

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}


#endif