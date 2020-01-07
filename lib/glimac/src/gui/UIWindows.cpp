#include <glimac/gui/UIWindows.hpp>

namespace glimac{
	void cubesWindow(Scene &scene, CubeList &cubeList,const glm::vec3 &position,ColorCubeInst &cubeEdgesObj){
		ImGui::Begin("Cubes");
            ImGui::Text("Change cube type");
            if (ImGui::Button("Dirt"))
            {
                cubeList.type(scene, position, DIRT);
            }ImGui::SameLine();
            if (ImGui::Button("Water"))
            {
                cubeList.type(scene, position, WATER);
            }
            if (ImGui::Button("Color"))
            {
                cubeList.type(scene, position, COLOR, glm::vec3(1,0,0));
            }ImGui::SameLine();
            if (ImGui::Button("Light"))
            {
                cubeList.type(scene, position, LIGHT);
            }

            ImGui::Text("Terrain options");
            if (ImGui::Button("Dig"))
            {
                cubeList.dig(scene, cubeEdgesObj);
            }ImGui::SameLine();
            if (ImGui::Button("Extrude"))
            {
                cubeList.extrude(scene, cubeEdgesObj);
            }
        ImGui::End();
	}

	void lightWindow(Scene &scene){
		ImGui::Begin("Light");
            ImGui::Text("Day Time / Night time");
            if (ImGui::Button("Switch"))
            {
                if(scene.lighting().sunLightInt()== glm::vec3(0,0,0)){
                    scene.changeLighting().activateSun();
                    
                }else{
                    scene.changeLighting().deactivateSun();
                }
               
            }
        ImGui::End();
	}
}

