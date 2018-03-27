#pragma once

#include "Buffer.h"
#include "GLobject.h"
#include "Program.h"
#include <iostream>

#include <GL\glew.h>
#include <stdarg.h>

struct Attribute
{
	GLuint _index;
	GLint _size;
	GLenum _type;
	GLboolean _normalized;
	GLsizei _stride;
	union
	{
		const GLvoid * _pointer;
		GLuint _offset;
	};

	Attribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer) :
		_index(index), _size(size), _type(type), _normalized(normalized), _stride(stride), _pointer(pointer)
	{}

	Attribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint offset) :
		_index(index), _size(size), _type(type), _normalized(normalized), _stride(stride), _offset(offset)
	{}
};

template <GLobjectType Type>
class VertexArray;

template<>
class VertexArray<GLobjectType::TARGET> : public GLobject
{
private:
	VertexArray(const VertexArray &);

public:
	VertexArray() : GLobject() { glGenVertexArrays(1, &_objectId); }
	~VertexArray() { glDeleteVertexArrays(1, &_objectId); }

	void bind(void) const override   { glBindVertexArray(_objectId); }
	void unbind(void) const override { glBindVertexArray(0); }

	void bindAttribute(const Buffer<GLobjectType::TARGET> & vertexBuffer, Attribute attr)
	{
		glBindVertexArray(_objectId);
		glBindBuffer(vertexBuffer.getTarget(), vertexBuffer.getId());
		glVertexAttribPointer(attr._index, attr._size, attr._type, attr._normalized, attr._stride, attr._pointer);
		glEnableVertexAttribArray(attr._index);
		glBindBuffer(vertexBuffer.getTarget(), 0);
		glBindVertexArray(0);
	}
	void bindAttributes(const Buffer<GLobjectType::TARGET> & vertexBuffer, GLuint count, ...)
	{
		va_list args;

		glBindVertexArray(_objectId);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.getId());

		va_start(args, count);
		for (GLuint i = 0; i < count; i++)
		{
			Attribute attr = va_arg(args, Attribute);
			glVertexAttribPointer(
				attr._index,
				attr._size,
				attr._type,
				attr._normalized,
				attr._stride,
				attr._pointer
			);
			glEnableVertexAttribArray(attr._index);
		}
		va_end(args);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void bindBuffer(const Buffer<GLobjectType::TARGET> & buffer)
	{
		glBindVertexArray(_objectId);
		glBindBuffer(buffer.getTarget(), buffer.getId());
		glBindVertexArray(0);
		glBindBuffer(buffer.getTarget(), 0);
	}
	void unbindBuffer(const Buffer<GLobjectType::TARGET> & buffer)
	{
		glBindVertexArray(_objectId);
		glBindBuffer(buffer.getTarget(), 0);
		glBindVertexArray(0);
	}
};

template<>
class VertexArray<GLobjectType::DSA> : public GLobject
{
private:
	VertexArray(const VertexArray&);

public:
	VertexArray() : GLobject() { glCreateVertexArrays(1, &_objectId); }
	~VertexArray() { glDeleteVertexArrays(1, &_objectId); }

	void bind(void) const override { glBindVertexArray(_objectId); }
	void unbind(void) const override { glBindVertexArray(0); }

	void bindAttribute(GLuint bindingIndex, Attribute attr)
	{
		glEnableVertexArrayAttrib(_objectId, attr._index);
		glVertexArrayAttribFormat(_objectId, attr._index, attr._size, attr._type, attr._normalized, attr._offset);
		glVertexArrayAttribBinding(_objectId, attr._index, bindingIndex);
	}

	void bindAttributes(GLuint bindingIndex, GLuint count, ...)
	{
		va_list args;
		va_start(args, count);
		for (GLuint i = 0; i < count; i++)
		{
			Attribute attr = va_arg(args, Attribute);
			glEnableVertexArrayAttrib(_objectId, attr._index);
			glVertexArrayAttribFormat(
				_objectId,
				attr._index,
				attr._size,
				attr._type,
				attr._normalized,
				attr._offset
			);
			glVertexArrayAttribBinding(_objectId, attr._index, bindingIndex);
		}
		va_end(args);
	}
};
