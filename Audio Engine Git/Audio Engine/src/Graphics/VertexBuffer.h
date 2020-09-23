#pragma once

#include "Renderer.h"

class VertexBuffer {

private:
	unsigned int m_RendererID;
	unsigned int drawHint = 0;

public:
	VertexBuffer() {};
	// Size in bytes
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void unBind() const;
};

