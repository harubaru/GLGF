#version 330 core

out vec4 Fragment;

in VS_OUT {
	vec2 TexCoord;
} fs_in;

uniform sampler2D image;
uniform int parallaxbg;
uniform vec2 parallaxoffset;

void main()
{
	if (parallaxbg == 0) {
		Fragment = texture(image, fs_in.TexCoord);
	} else {
		Fragment = texture(image, fs_in.TexCoord + parallaxoffset);
	}

	if (Fragment.a < 0.05)
		discard;
}
