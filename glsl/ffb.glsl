#version 330 core

out vec4 Fragment;

in VS_OUT {
	vec2 TexCoord;
} fs_in;

uniform sampler2D image;

vec4 none(void)
{
	return texture(image, fs_in.TexCoord);
}

vec4 blur(void)
{
	const float blurSizeH = 1.0 / 640;
	const float blurSizeV = 1.0 / 480;

	vec4 sum = vec4(0.0);

	for (int x = -4; x <= 4; x++) {
		for (int y = -4; y <= 4; y++) {
			sum += texture(image, vec2(fs_in.TexCoord.x + x * blurSizeH, fs_in.TexCoord.y + y * blurSizeV)) / 81.0;
		}
	}

	return sum;
}

vec4 sobel(void)
{
	vec4 top         = texture(image, vec2(fs_in.TexCoord.x, fs_in.TexCoord.y + 1.0 / 200.0));
	vec4 bottom      = texture(image, vec2(fs_in.TexCoord.x, fs_in.TexCoord.y - 1.0 / 200.0));
	vec4 left        = texture(image, vec2(fs_in.TexCoord.x - 1.0 / 300.0, fs_in.TexCoord.y));
	vec4 right       = texture(image, vec2(fs_in.TexCoord.x + 1.0 / 300.0, fs_in.TexCoord.y));
	vec4 topLeft     = texture(image, vec2(fs_in.TexCoord.x - 1.0 / 300.0, fs_in.TexCoord.y + 1.0 / 200.0));
	vec4 topRight    = texture(image, vec2(fs_in.TexCoord.x + 1.0 / 300.0, fs_in.TexCoord.y + 1.0 / 200.0));
	vec4 bottomLeft  = texture(image, vec2(fs_in.TexCoord.x - 1.0 / 300.0, fs_in.TexCoord.y - 1.0 / 200.0));
	vec4 bottomRight = texture(image, vec2(fs_in.TexCoord.x + 1.0 / 300.0, fs_in.TexCoord.y - 1.0 / 200.0));
	vec4 sx = -topLeft - 2 * left - bottomLeft + topRight   + 2 * right  + bottomRight;
	vec4 sy = -topLeft - 2 * top  - topRight   + bottomLeft + 2 * bottom + bottomRight;
	vec4 sobel = sqrt(sx * sx + sy * sy);
	return sobel;
}

void main()
{
	Fragment = none();
}
