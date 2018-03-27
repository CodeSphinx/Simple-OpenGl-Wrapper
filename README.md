# Simple-OpenGl-Wrapper
This library simplifies the opengl program development process by allow users easily access and manipulate OpenGL objects through class wrappers.

At the moment, all code is provided in the corresponding header file for simplicity. In the future code will be moved into their own source files.
</br>
#### Simple Rectangle Example (Utilizing Bind-Target)
```c++
void drawRectangle(Rect rectangle, Color color)
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
  
  VertexArray<GLobjectType::TARGET> VAO;
  Buffer<GLobjectType::TARGET> VBO(GL_ARRAY_BUFFER);
  Buffer<GLobjectType::TARGET> EBO(GL_ELEMENT_ARRAY_BUFFER);
  VBO.BufferData(vertexData, 12, GL_STATIC_DRAW);
  EBO.BufferData(indexData, 6, GL_STATIC_DRAW);
  
  Attribute attr(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  VAO.bindBuffer(EBO);
  VAO.bindAttribute(VBO, attr);
  
  simpleRect.useProgram();
  GLint loc = glGetUniformLocation(simpleRect.getId(), "color");
  glUniform4f(loc, (GLfloat)(color.r) / 255, (GLfloat)(color.g) / 255, (GLfloat)(color.b) / 255, (GLfloat)(color.a) / 255);

  VAO.bind();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  VAO.unbind();
  simpleRect.unuseProgram();
}
```
#### Simple Rectangle Example (Utilizing Direct State Access)
```c++
void drawRectangle(Rect rectangle, Color color)
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
  VBO.bufferData(vertexData, 12, GL_STATIC_DRAW);

  Buffer<GLobjectType::DSA> EBO;
  EBO.bufferData(indexData, 6, GL_STATIC_DRAW);

  VAO.bindBuffer(VBO, GL_ARRAY_BUFFER);
  VAO.bindBuffer(EBO, GL_ELEMENT_ARRAY_BUFFER);

  Attribute attr(0, 3, GL_FLOAT, GL_FALSE, 0);
  VAO.bindAttribute(0, attr);

  simpleRect.use();
  VAO.drawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  simpleRect.unuse();
```

# Requirements
- GLEW (At the moment)

# Disclaimer
I am still in process of learning OpenGL, so expect stuff to not work.
