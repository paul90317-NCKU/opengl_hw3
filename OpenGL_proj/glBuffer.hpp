#ifndef __GL_BUFFER_H
#define __GL_BUFFER_H
#include "comm.hpp"
#include "glObject.hpp"

class glBuffer : public glObject {
private:
	GLuint ID;
	GLenum BIND_TARGET;
public:
	glBuffer(void*, size_t, GLenum, GLenum draw_mode=GL_STATIC_DRAW);
	void UnBind();
	void Delete();
	void Bind();
};

#endif // !__GL_BUFFER_H


