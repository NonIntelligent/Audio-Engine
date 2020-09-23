#include "VertexBuffer.h"

#include "Renderer.h"

VertexBuffer::VertexBuffer(const void * data, unsigned int size) {
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));

	if(drawHint != 0) {
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, drawHint));
	}
	else {
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}
}

VertexBuffer::~VertexBuffer() {
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::bind() const{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::unBind() const{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}