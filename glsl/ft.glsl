#version 330 core

out vec4 Fragment;

in VS_OUT {
	vec2 TexCoord;
} fs_in;

uniform sampler2D text;
uniform vec3 color;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, fs_in.TexCoord).r);
    Fragment = vec4(color, 1.0) * sampled;
}  