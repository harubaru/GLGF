#include <sampler.h>

sampler_createinfo_t sampler_createinfo_default()
{
	sampler_createinfo_t d = { GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST, -1000.f, 1000.f, 0.f };
	return d;
}

GLuint sampler_init(sampler_createinfo_t createinfo) 
{
	GLuint sampler;
	
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, createinfo.wrap_s);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, createinfo.wrap_t);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, createinfo.min_filter);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, createinfo.mag_filter);
	glSamplerParameterf(sampler, GL_TEXTURE_MIN_LOD, createinfo.min_lod);
	glSamplerParameterf(sampler, GL_TEXTURE_MAX_LOD, createinfo.max_lod);
	glSamplerParameterf(sampler, GL_TEXTURE_LOD_BIAS, createinfo.lod_bias);

	return sampler;
}

void sampler_bind(GLuint sampler, GLuint texunit)
{
	glBindSampler(texunit, sampler);
}

void sampler_destroy(GLuint sampler) 
{
	if (glIsSampler(sampler) == GL_FALSE)
		return;
	
	glDeleteSamplers(1, &sampler);
}
