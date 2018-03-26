#pragma once
#ifndef BUFFER_H
#define BUFFER_H
#include "GLobject.h"
#include <GL\glew.h>

template <GLobjectType Type>
class Buffer;

template<>
class Buffer<GLobjectType::TARGET> : public GLobject
{
private:
	GLenum _target;

	Buffer();
	Buffer(const Buffer&);

public:
	Buffer(GLenum target) : GLobject(), _target(target) { glGenBuffers(1, &_objectId); }
	~Buffer() { glDeleteBuffers(1, &_objectId); }

	template<typename T>
	void BufferData(T * data, GLuint size, GLenum usage)
	{
		glBindBuffer(_target, _objectId);
		glBufferData(_target, sizeof(T) * size, data, usage);
		glBindBuffer(_target, 0);
	}

	GLenum getTarget(void) const { return _target; }

	void bind(void) const override   { glBindBuffer(_target, _objectId); }
	void unbind(void) const override { glBindBuffer(_target, 0); }
};

template<>
class Buffer<GLobjectType::DSA> : public GLobject
{
}
#endif
