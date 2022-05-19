#include "comm.hpp"
#include "VertexArray.hpp"

VertexArray::VertexArray(int _draw_count) {
	draw_number = _draw_count;
	glGenVertexArrays(1, &ID);
	//glBindVertexArray(ID);
}
VertexArray::VertexArray()
{
}
VertexArray &VertexArray::Attrib(GLuint layout, GLuint numComponents, GLenum dataType, GLsizeiptr stride,void* offset) {
	glVertexAttribPointer(layout, numComponents, dataType, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	return *this;
}
void VertexArray::UnBindAll(){
	glBindVertexArray(0);
	for (auto buf : bufs) {
		buf.UnBind();
	}
}
void VertexArray::UnBind()
{
	glBindVertexArray(0);
}
void VertexArray::Bind() {
	glBindVertexArray(ID);
}
void VertexArray::Delete() {
	glDeleteBuffers(1, &ID);
	for (auto buf : bufs) {
		buf.Delete();
	}
}
VertexArray &VertexArray::Add(myGL_Object buf) {
	bufs.push_back(buf);
	return *this;
}