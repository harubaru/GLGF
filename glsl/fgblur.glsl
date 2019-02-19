#version 330 core

layout (location = 0) out vec4 Fragment;

in VS_OUT {
	vec2 TexCoord;
} fs_in;

uniform sampler2D t;
uniform int horizontal;
	
void main()
{
	const float w[5] = float[](.227027,.1945946,.1216216,.054054,.016216);
	vec2 o=1.0/textureSize(t, 0);
	vec3 r=texture(t,fs_in.TexCoord).rgb*w[0];
	if (horizontal == 1) {
		for(int i=1;i<5;++i) {r+=texture(t,fs_in.TexCoord+vec2(o.x*i,.0)).rgb*w[i];r+=texture(t,fs_in.TexCoord-vec2(o.x*i,.0)).rgb*w[i];}
	} else {
		for(int i=1;i<5;++i) {r+=texture(t,fs_in.TexCoord+vec2(0.0,o.y*i)).rgb*w[i];r+=texture(t,fs_in.TexCoord-vec2(0.0,o.y*i)).rgb*w[i];}
	}
	Fragment=vec4(r,1.0);
}
