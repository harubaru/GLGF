#version 330 core

layout (location = 0) out vec4 Fragment;
layout (location = 1) out vec4 Fragment2;

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

	float linear_brightness = dot(Fragment.rgb, vec3(0.2126, 0.7152, 0.0722));
	if (linear_brightness > 1.0) {
		Fragment2 = vec4(Fragment.rgb, 1.0);
	} else {
		Fragment2 = vec4(vec3(0.0), 1.0);
	}
}
