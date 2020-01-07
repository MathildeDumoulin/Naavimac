#include <glimac/gui/UIWindows.hpp>

namespace glimac{
	void cubesWindow(Scene &scene, CubeList &cubeList,const glm::vec3 &position,ColorCubeInst &cubeEdgesObj){
		ImGui::Begin("Cubes");
            ImGui::Text("Change cube type");
            if (ImGui::Button("Dirt"))
            {
                cubeList.type(scene, position, DIRT);
            }
            if (ImGui::Button("Water"))
            {
                cubeList.type(scene, position, WATER);
            }
            if (ImGui::Button("Light"))
            {
                cubeList.type(scene, position, LIGHT);
            }

            static float col1[3]={ 1.0f,0.0f,0.0f};
            ImGui::ColorEdit3("Color", col1);
            //std::cout << col1[0] << std::endl;
            if (ImGui::Button("Color"))
            {
                cubeList.type(scene, position, COLOR, glm::vec3(col1[0],col1[1],col1[2]));
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

	void lightWindow(Scene &scene, IMGUIWindowManager &interface){
		ImGui::Begin("Lighting");
            ImGui::Text("Day Time / Night time");
            if (ImGui::Button("Switch"))
            {
                if(scene.lighting().sunLightInt()== glm::vec3(0,0,0)){
                    scene.changeLighting().activateSun();
                    interface.clearColor(ImVec4(0.7,0.7,0.7,1));
                    
                }else{
                    scene.changeLighting().deactivateSun();
                    interface.clearColor(ImVec4(0,0,0,1));
                }
               
            }
            ImGui::Text("Light Intensity");
        ImGui::End();
	}

}

