#pragma once //Ignored on Linux/OSX
#ifndef GL_OBJECT_H
#define GL_OBJECT_H

#include <GL\glew.h>

class GLobject
{
protected:
	GLuint _objectId;

public:
	GLobject(void);
	virtual ~GLobject() = 0;

	virtual void bind(void) const;
	virtual void unbind(void) constt;

	GLuint getId(void) const;
};

#endif
