#ifndef __GL_TEXTURE_H
#define __GL_TEXTURE_H

#include "glObject.hpp"

class glTexture :public glObject
{
private:
	GLuint ID;
	GLenum BIND_TARGET;
	int widthImg, heightImg, numColCh;
public:
	glTexture(GLenum bindTarget);
	void UnBind();
	void Delete();
	void Bind();
	glTexture &Generate(const char* filename);
	glTexture &Parameteri(GLenum key, GLenum value);
};

#endif