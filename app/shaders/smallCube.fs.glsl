#version 330

//IN
in vec3 vPosition_vs; //View space vertex position
in vec3 vNormal_vs; //View space vertex normal
in vec2 vTexCoords; //Vertex texture coords
in vec3 vColor;

//Uniforms
uniform sampler2D uTexture;

out vec3 fFragColor;

void main() {
    fFragColor = vec3(1,1,1);
}