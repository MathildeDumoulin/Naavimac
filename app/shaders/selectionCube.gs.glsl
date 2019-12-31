#version 330

layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 u_MVMatrix;
uniform mat4 u_MVPMatrix;

void main()
{
    float baseThickness = 0.02;
    float minThickness = 0.004;

    //Get the positions in the clip-space
    vec4 p1 = gl_in[0].gl_Position;
    vec4 p2 = gl_in[1].gl_Position;

    //vec4 direction
    vec4 direction = normalize(p2 - p1);

    //Space screen direction and normal
    vec2 dir = normalize(p2.xy - p1.xy);
    vec2 normal = vec2(-dir.y, dir.x);

    float radius = baseThickness - abs(p1.z)*minThickness;
    if(radius < minThickness) radius = minThickness;

    vec4 offset = vec4(normal * radius, 0, 0);

    vec4 coords[4];
    coords[0] = p1 - (radius/2 * direction) + offset * p1.w;
    coords[1] = p1 - (radius/2 * direction) - offset * p1.w;
    coords[2] = p2 + (radius/2 * direction) + offset * p2.w;
    coords[3] = p2 + (radius/2 * direction) - offset * p2.w;

    for (int i = 0; i < 4; ++i) {
        gl_Position = coords[i];
        EmitVertex();
    }
    EndPrimitive();
}