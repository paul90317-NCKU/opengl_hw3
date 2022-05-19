#ifndef __MY_GL_TEXTURE_H
#define __MY_GL_TEXTURE_H

#include "myGL_Object.hpp"

class myGL_Texture :public myGL_Object
{
private:
	GLuint ID;
	GLenum BIND_TARGET;
	int widthImg, heightImg, numColCh;
public:
	myGL_Texture(GLenum bindTarget);
	void UnBind();
	void Delete();
	void Bind();
	myGL_Texture &Generate(const char* filename);
	myGL_Texture &Parameteri(GLenum key, GLenum value);
};

#endif