#version 330 core

out vec4 Fragment;

in VS_OUT {
	vec2 TexCoord;
} fs_in;

uniform sampler2D image;

void main()
{
	Fragment = texture(image, fs_in.TexCoord);

	if (Fragment.a < 0.05)
		discard;
}
