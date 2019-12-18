#version 330

//IN
in vec3 vPosition_vs; //View space vertex position
in vec3 vNormal_vs; //View space vertex normal
in vec2 vTexCoords; //Vertex texture coords

//Uniforms
uniform sampler2D uTexture;

out vec4 fFragColor;

void main() {
    fFragColor = vec4(1,0,0,0.5);
}