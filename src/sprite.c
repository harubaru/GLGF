#include <stdio.h>
#include <sprite.h>

static GLfloat SpriteVertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
};


static GLuint m_VertexArrayObject;
static GLuint m_VertexArrayBuffer;

static mat4x4 projection;

void sprite_init()
{
	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject);

	glGenBuffers(1, &m_VertexArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SpriteVertices), SpriteVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void sprite_destroy()
{
	glDeleteVertexArrays(1, &m_VertexArrayObject);
	glDeleteBuffers(1, &m_VertexArrayBuffer);
}

void sprite_projection(int w, int h)
{
	mat4x4_identity(projection);
	mat4x4_ortho(projection, 0.0f, (float)w, 0.0f, (float)h, -1, 1);	
}

void sprite_draw(GLuint texture, GLuint shader, vec2 position, vec2 size)
{
	mat4x4 M;
	mat4x4_identity(M);

	mat4x4_translate(M, position[0], position[1], 0.0f);
	mat4x4_scale_aniso(M, M, size[0], size[1], 1.0f);

	shader_bind(shader);
	texture_bind(texture, 0);
	glUniformMatrix4fv(glGetUniformLocation(shader, "Model"), 1, GL_FALSE, *M);
	glUniformMatrix4fv(glGetUniformLocation(shader, "Projection"), 1, GL_FALSE, *projection);
	glUniform1i(glGetUniformLocation(shader, "use_spritesheet"), 0);

	glBindVertexArray(m_VertexArrayObject);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}
