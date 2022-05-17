#include "glBuffer.hpp"

glBuffer::glBuffer(void *values, size_t size,GLenum bindTarget, GLenum usage):
	BIND_TARGET(bindTarget)
{
	glGenBuffers(1, &ID);
	glBindBuffer(BIND_TARGET, ID);
	glBufferData(BIND_TARGET, size, values, usage);
}
void glBuffer::UnBind() {
	glBindBuffer(BIND_TARGET, 0);
}
void glBuffer::Delete() {
	glDeleteBuffers(1, &ID);
}
void glBuffer::Bind() {
	glBindBuffer(BIND_TARGET, ID);
}