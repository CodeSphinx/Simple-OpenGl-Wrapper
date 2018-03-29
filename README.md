# Simple-OpenGl-Wrapper
This library simplifies the opengl program development process by allow users easily access and manipulate OpenGL objects through class wrappers.

At the moment, all code is provided in the corresponding header file for simplicity. In the future code will be moved into their own source files.
</br>
#### Simple Rectangle Example
```c++
extern void drawRectXDSA(Rect rect, Color color, GLfloat rotation = 0.0f, GLfloat scale = 1.0f)
{
	static Program simpleRect("Primitive.vert", "Primitive.frag");

	GLfloat vertexData[] = {
		rect.x, rect.y, 0.0f,
		rect.x, rect.y + rect.h, 0.0f,
		rect.x + rect.w, rect.y + rect.h, 0.0f,
		rect.x + rect.w, rect.y, 0.0f
	};

	const GLuint indexData[] = {
		0, 1, 3,
		1, 2, 3
	};

	VertexArray<GLobjectType::DSA> VAO;
	Buffer<GLobjectType::DSA> VBO;
	Buffer<GLobjectType::DSA> EBO;

	VBO.bufferData(vertexData, 12, GL_STATIC_DRAW);
	EBO.bufferData(indexData, 6, GL_STATIC_DRAW);

	VAO.bindVertexBuffer(VBO, 0, 0, 3 * sizeof(GLfloat));
	VAO.bindElementBuffer(EBO);

	Attribute attr(0, 3, GL_FLOAT, GL_FALSE, 0);
	VAO.bindAttribute(0, attr);

	simpleRect.useProgram();
	glm::mat4 modelMatrix;
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));

	glUniformMatrix4fv(glGetUniformLocation(simpleRect.getId(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniform4f
	(
		glGetUniformLocation(simpleRect.getId(), "color"),
		(GLfloat)(color.r) / 255,
		(GLfloat)(color.g) / 255,
		(GLfloat)(color.b) / 255,
		(GLfloat)(color.a) / 255
	);

	VAO.drawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	simpleRect.unuseProgram();
}
```

# Requirements
- GLEW (At the moment)

# Disclaimer
I am still in process of learning OpenGL, so expect stuff to not work.
