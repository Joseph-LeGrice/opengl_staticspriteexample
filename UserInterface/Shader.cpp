#include "Shader.h"

#include <iostream>
#include <fstream>


Shader::Shader()
{
	std::ifstream vertexSourceFile("SimpleVertexShader.vert");
	std::string vertexSourceString((std::istreambuf_iterator<char>(vertexSourceFile)), std::istreambuf_iterator<char>());
	const GLchar *vertexSource = vertexSourceString.data();
	vertexSourceFile.close();

	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexShader, 1, (const GLchar**)&vertexSource, 0);
	glCompileShader(m_vertexShader);

	GLint vertexShaderDidCompile;
	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &vertexShaderDidCompile);
	if (vertexShaderDidCompile == GL_FALSE)
	{
		GLint maxLength;
		glGetShaderiv(m_vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		char *vertexInfoLog = (char *)malloc(maxLength);

		glGetShaderInfoLog(m_vertexShader, maxLength, &maxLength, vertexInfoLog);

		std::cout << vertexInfoLog;

		free(vertexInfoLog);
		return;
	}

	std::ifstream fragmentSourceFile("SimpleFragmentShader.frag");
	std::string fragmentSourceString((std::istreambuf_iterator<char>(fragmentSourceFile)), std::istreambuf_iterator<char>());
	const GLchar *fragmentSource = fragmentSourceString.data();
	fragmentSourceFile.close();

	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	glCompileShader(m_fragmentShader);

	GLint fragmentShaderDidCompile;
	glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &fragmentShaderDidCompile);
	if (fragmentShaderDidCompile == GL_FALSE)
	{
		GLint maxLength;
		glGetShaderiv(m_fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		char *fragmentInfoLog = (char *)malloc(maxLength);

		glGetShaderInfoLog(m_fragmentShader, maxLength, &maxLength, fragmentInfoLog);

		std::cout << fragmentInfoLog;

		free(fragmentInfoLog);
	}

	m_shaderHandle = glCreateProgram();
	glAttachShader(m_shaderHandle, m_vertexShader);
	glAttachShader(m_shaderHandle, m_fragmentShader);

	glBindAttribLocation(m_shaderHandle, 0, "in_Position");
	glBindAttribLocation(m_shaderHandle, 1, "in_UV");

	glLinkProgram(m_shaderHandle);
	glUseProgram(m_shaderHandle);

	m_mvpUniformId = glGetUniformLocation(m_shaderHandle, "ModelViewProjection");
}


Shader::~Shader()
{
	glUseProgram(0);
	glDetachShader(m_shaderHandle, m_vertexShader);
	glDetachShader(m_shaderHandle, m_fragmentShader);
	glDeleteProgram(m_shaderHandle);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
}

void Shader::SetMVP(glm::mat4 &mvp)
{
	glUniformMatrix4fv(m_mvpUniformId, 1, GL_FALSE, &mvp[0][0]);
}
