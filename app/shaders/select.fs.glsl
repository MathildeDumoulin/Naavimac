#version 330

//Uniforms
uniform sampler2D uTexture;

out vec4 fFragColor;

void main() {
    fFragColor = vec4(1,0,0,0.5);
}