#ifndef __GL_OBJECT_H
#define __GL_OBJECT_H
#include "comm.hpp"

class glObject {
public:
	virtual void UnBind() {};
	virtual void Delete() {};
	virtual void Bind() {};
};

#endif // !__GL_BUFFER_H


