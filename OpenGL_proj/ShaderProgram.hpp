#ifndef __SHADER_PROGRAM_HPP
#define __SHADER_PROGRAM_HPP

#include "comm.hpp"

class ShaderProgram{
public:
	ShaderProgram();
	ShaderProgram& Use();
	void Delete();
	ShaderProgram& AttachShader(const char*,GLenum);
	ShaderProgram& Uniform1i(const char* key, GLuint value);
	ShaderProgram& UniformMatrix4fv(const char* key, GLfloat *value, int count=1);
	ShaderProgram& UniformMatrix1fv(const char* key, GLfloat* value, int count=1);
	ShaderProgram& Link();
	GLuint ID;
private:
	std::vector<GLuint> shaders;
};

#endif