#pragma once

#include "Renderer.h"

class IndexBuffer {

private:
	unsigned int m_RendererID;
	unsigned int m_Count;
	unsigned int drawHint = 0;

public:
	IndexBuffer() {	};
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unBind() const;

	inline GLuint getCount() const {return m_Count;}
};

