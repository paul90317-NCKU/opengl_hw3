#ifndef __VERTEX_ARRAY_H
#define __VERTEX_ARRAY_H
#include "comm.hpp"
#include "myGL_Object.hpp"

#define addBuf(values,bindTarget,usage) Add(myGL_Buffer(values, sizeof(values), bindTarget, GL_STATIC_DRAW))


class VertexArray
{
private:
	GLuint ID;
	std::vector<myGL_Object> bufs;
public:
	int draw_number;
	VertexArray(int);
	VertexArray();
	VertexArray &Attrib(GLuint layout, GLuint numComponents, GLenum dataType, GLsizeiptr stride,void* offset=0);
	VertexArray &Add(myGL_Object buf);
	void UnBindAll();
	void UnBind();
	void Bind();
	void Delete();
};
#endif

