#ifndef __MY_GL_OBJECT_H
#define __MY_GL_OBJECT_H
#include "comm.hpp"

class myGL_Object {
public:
	virtual void UnBind() {};
	virtual void Delete() {};
	virtual void Bind() {};
};

#endif // !__GL_BUFFER_H


