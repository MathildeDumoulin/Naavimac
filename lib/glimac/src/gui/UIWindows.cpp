#include <glimac/gui/UIWindows.hpp>

namespace glimac{
	void cubesWindow(Scene &scene, CubeList &cubeList,const glm::vec3 &position,ColorCubeInst &cubeEdgesObj){
		ImGui::SetNextWindowSize(ImVec2(200, 200));
		ImGui::SetNextWindowPos(ImVec2(10, 10));
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
		ImGui::SetNextWindowSize(ImVec2(200, 120));
		ImGui::SetNextWindowPos(ImVec2(220, 10));
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

            static float f1=5.0f;
            ImGui::SliderFloat("", &f1, 0.0f, 15.0f, "intensity : %.1f");
            scene.changeLighting().pointLightsInt(glm::vec3(f1,f1,f1));

        ImGui::End();
	}

	void RBFWindow(Scene &scene, CubeList &cubeList){
        static float epsilon = 1.0f;
        ImGui::SetNextWindowSize(ImVec2(200, 80));
        ImGui::SetNextWindowPos(ImVec2(640, 10));
        ImGui::Begin("Extra parameters"); 
            {
                ImGui::SliderFloat("", &epsilon, 0.0f, 5.0f, "epsilon : %.1f");
            }
        ImGui::End();


		ImGui::SetNextWindowSize(ImVec2(200, 180));
		ImGui::SetNextWindowPos(ImVec2(430, 10));
        
		static char rbfFile[128] = "cp1.txt";
        ImGui::Begin("Files"); 

			ImGui::Text("Load control points :");
            {
                ImGui::InputText("", rbfFile, IM_ARRAYSIZE(rbfFile));
            }

            ImGui::Text("Choose RBF :");
			

            if (ImGui::Button("Multiquadric"))
            {
                cubeList.applyRBF(scene, rbfFile,1,epsilon);   
            }

            if (ImGui::Button("Gaussian"))
            {
                cubeList.applyRBF(scene, rbfFile,2,epsilon);
            }

            if (ImGui::Button("Inv. Quadratic"))
            {
                cubeList.applyRBF(scene, rbfFile,3,epsilon);   
            }

        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(500, 60));
        ImGui::SetNextWindowPos(ImVec2(10, 800));

        ImGui::Begin("Presets"); 
        {
            if (ImGui::Button("Islands"))
            {
                cubeList.applyRBF(scene, "cp7.txt",3,epsilon,1);   
            }ImGui::SameLine();
            if (ImGui::Button("Big lake"))
            {
                cubeList.applyRBF(scene, "cp1.txt",3,0.2, 0);   
            }ImGui::SameLine(); 
            if (ImGui::Button("Beach"))
            {
                cubeList.applyRBF(scene, "cp2.txt",3,2.5, 0);   
            }
            ImGui::SameLine();
            if (ImGui::Button("Coast"))
            {
                cubeList.applyRBF(scene, "cp8.txt",2,1.2, 1);   
            }ImGui::SameLine();
            if (ImGui::Button("Full Ocean"))
            {
                cubeList.FullOcean(scene);
            }ImGui::SameLine();
            if (ImGui::Button("Full Continent"))
            {
                cubeList.FullGround(scene);
            }

            
        }
        ImGui::End();
        
    }
}

