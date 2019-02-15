#version 330 core

layout (location = 0) in vec4 vertex;

uniform mat4 Model;
uniform mat4 Projection;

out VS_OUT {
    vec2 TexCoord;
} vs_out;

void main()
{
    vs_out.TexCoord = vertex.zw;
    gl_Position = Projection * Model * vec4(vertex.xy, 0.0, 1.0);
}
