#include "myGL_Buffer.hpp"

myGL_Buffer::myGL_Buffer(void *values, size_t size,GLenum bindTarget, GLenum usage):
	BIND_TARGET(bindTarget)
{
	glGenBuffers(1, &ID);
	glBindBuffer(BIND_TARGET, ID);
	glBufferData(BIND_TARGET, size, values, usage);
}
void myGL_Buffer::UnBind() {
	glBindBuffer(BIND_TARGET, 0);
}
void myGL_Buffer::Delete() {
	glDeleteBuffers(1, &ID);
}
void myGL_Buffer::Bind() {
	glBindBuffer(BIND_TARGET, ID);
}