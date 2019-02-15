#version 330 core

out vec4 Fragment;

in VS_OUT {
	vec2 TexCoord;
} fs_in;

void main()
{
	Fragment = vec4(vec3(0.01, 0.01, 0.01), 1.0);

	if (Fragment.a < 0.5)
		discard;
}
