#pragma once

#include <gl\glew.h>
#include <glm\glm.hpp>

class Shader
{
public:
	Shader();
	~Shader();

	void SetMVP(glm::mat4&);

private:
	GLuint m_fragmentShader;
	GLuint m_vertexShader;
	GLuint m_shaderHandle;
	GLuint m_mvpUniformId;
};

