#pragma once
#include "Error.h"
#include "GLobject.h"

#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <initializer_list>
#include <vector>

struct Shader
{
	char * _shaderSource;
	GLenum _shaderType;

	Shader(char * shaderSource, GLenum shaderType) : _shaderSource(shaderSource), _shaderType(shaderType) {};
};


class Program : public GLobject
{
	GLuint loadShader(const char * filePath, GLuint type)
	{
		//Read Shader Source
		std::ifstream shaderFile(filePath, std::ios::in);
		std::string shaderSource;

		if (shaderFile.is_open())
		{
			std::stringstream sstr;
			sstr << shaderFile.rdbuf();
			shaderSource = sstr.str();
			shaderFile.close();
		}
		else
			handleError("***UNABLE TO OPEN SHADER FILE***", false);


		//Compile Shader
		GLuint shader = glCreateShader(type);
		const char * shaderSource_cStr = shaderSource.c_str();

		glShaderSource(shader, 1, &shaderSource_cStr, nullptr);
		glCompileShader(shader);

		//Error Checking
		GLint success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			handleError(infoLog, false);
			glDeleteShader(shader);
			return 0;
		}

		glAttachShader(_objectId, shader);
		return shader;
	}

public:
	Program()
	{
		_objectId = glCreateProgram();
	}
	Program(const char * vertexShader, const char * fragmentShader)
	{
		_objectId = glCreateProgram();

		GLuint vertexShaderId   = this->loadShader(vertexShader, GL_VERTEX_SHADER);
		GLuint fragmentShaderId = this->loadShader(fragmentShader, GL_FRAGMENT_SHADER);
		
		glLinkProgram(_objectId);

		glDetachShader(_objectId, vertexShaderId);
		glDetachShader(_objectId, fragmentShaderId);
		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
	}
	Program(std::initializer_list<Shader> shaders)
	{
		_objectId = glCreateProgram();
		std::vector<GLuint> shaderId;

		for (auto shader : shaders)
			shaderId.push_back(this->loadShader(shader._shaderSource, shader._shaderType));

		glLinkProgram(_objectId);

		for (GLuint id : shaderId)
		{
			glDetachShader(_objectId, id);
			glDeleteShader(id);
		}
	}

	~Program()
	{
		glDeleteProgram(_objectId);
	}

	GLuint getUniformLocation(const char * uniformName) const
	{
		return glGetUniformLocation(_objectId, uniformName);
	}

	void useProgram(void) const { glUseProgram(_objectId); }
	void unuseProgram(void) const { glUseProgram(0); }
};
