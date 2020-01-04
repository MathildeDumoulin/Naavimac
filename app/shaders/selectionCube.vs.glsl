#version 330

//Vertex Attributes
layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;
layout(location = 3) in vec3 aOffset;
layout(location = 4) in vec3 aColor;

//Uniform transformation matrix
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;


void main() {
    vec3 aVertexPosition2 = aVertexPosition * 1.02 + aOffset;

    //Homogene coords
    vec4 vertexPosition = vec4(aVertexPosition2, 1);

    //gl_Position
    gl_Position = uMVPMatrix * vertexPosition;
}