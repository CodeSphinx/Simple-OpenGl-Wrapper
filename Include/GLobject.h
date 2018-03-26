#pragma once //Ignored on Linux/OSX
#ifndef GL_OBJECT_H
#define GL_OBJECT_H
#include <GL\glew.h>

enum struct GLobjectType : int
{
	DSA = 0,
	TARGET = 1
};

class GLobject
{
protected:
	GLuint _objectId;

public:
	GLobject(void) {};
	virtual ~GLobject() = 0 {};

	virtual void bind(void) const {};
	virtual void unbind(void) const {};

	GLuint getId(void) const {
		return _objectId;
	}
};
#endif
