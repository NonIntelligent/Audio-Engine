#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:
	GLuint m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void bind() const;
	void unBind() const;
};
