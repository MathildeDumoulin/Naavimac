#version 330

//Vertex Attributes
layout(location = 0) in vec3 aVertexPosition;

//Uniform transformation matrix
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;


void main() {
    //Homogene coords
    vec4 vertexPosition = vec4(aVertexPosition, 1);

    //gl_Position
    gl_Position = uMVPMatrix * vertexPosition;
}
