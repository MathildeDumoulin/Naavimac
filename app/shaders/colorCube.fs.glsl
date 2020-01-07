#version 330

#define NB_LIGHTS_MAX 5

//IN
in vec3 vPosition_vs; //View space vertex position
in vec3 vNormal_vs; //View space vertex normal
in vec2 vTexCoords; //Vertex texture coords
in vec3 vColor;

//Uniforms
uniform mat4 uMVMatrix;

uniform vec3 uSunLightDir;
uniform vec3 uSunLightInt;
uniform vec3 uPointLightsInt;
uniform vec3 uPointLights[NB_LIGHTS_MAX];
uniform int uNbLight;

out vec3 fFragColor;

vec3 blinnPhongDirectional() {
    vec3 sunLightDir_vs = vec3(uMVMatrix * vec4(uSunLightDir, 0));

    vec3 diff = vColor;

    vec3 Li = uSunLightInt;
    vec3 wi = normalize(sunLightDir_vs);
    vec3 w0 = normalize(-vPosition_vs);
    vec3 halfVec = (w0 + wi) / 2;
    float shininess = 1;

    vec3 color = Li * (diff * (dot(wi, vNormal_vs)) + diff * pow((dot(halfVec, vNormal_vs)), shininess));
    return color;
}

vec3 blinnPhongPoint(vec3 ptLight) {
    vec3 pointLightPos_vs = vec3(uMVMatrix * vec4(ptLight, 1));

    vec3 diff = vColor;

    vec3 uLightIntensity = uPointLightsInt;
    float shininess = 1;

    vec3 Li = uLightIntensity / pow(distance(pointLightPos_vs, vPosition_vs), 2);
    vec3 wi = normalize(pointLightPos_vs -vPosition_vs);
    vec3 w0 = normalize(pointLightPos_vs);
    vec3 halfVec = (w0 + wi) / 2;
    vec3 color = Li * (diff * (dot(wi, vNormal_vs)) + diff * pow((dot(halfVec, vNormal_vs)), shininess));
    return color;
}

void main() {
    fFragColor = blinnPhongDirectional();
    for(int i = 0; i < uNbLight; ++i) {
        fFragColor += abs(blinnPhongPoint(uPointLights[i]));
    } 
}