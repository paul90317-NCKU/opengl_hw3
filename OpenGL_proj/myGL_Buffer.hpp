#ifndef __MY_GL_BUFFER_H
#define __MY_GL_BUFFER_H
#include "comm.hpp"
#include "myGL_Object.hpp"

class myGL_Buffer : public myGL_Object {
private:
	GLuint ID;
	GLenum BIND_TARGET;
public:
	myGL_Buffer(void*, size_t, GLenum, GLenum draw_mode=GL_STATIC_DRAW);
	void UnBind();
	void Delete();
	void Bind();
};

#endif // !__GL_BUFFER_H


