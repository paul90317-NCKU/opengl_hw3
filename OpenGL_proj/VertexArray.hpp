#ifndef __VERTEX_ARRAY_H
#define __VERTEX_ARRAY_H
#include "comm.hpp"
#include "glBuffer.hpp"

#define addBuf(values,bindTarget,usage) Add(glBuffer(values, sizeof(values), bindTarget, GL_STATIC_DRAW))


class VertexArray
{
private:
	GLuint ID;
	std::vector<glObject> bufs;
public:
	int draw_number;
	VertexArray();
	VertexArray &Attrib(GLuint layout, GLuint numComponents, GLenum dataType, GLsizeiptr stride,void* offset=0);
	VertexArray &Add(glObject buf);
	void UnBindAll();
	void UnBind();
	void Bind();
	void Delete();
};
#endif

