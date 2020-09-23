#pragma once

#include <vector>
#include "GL/glew.h"
#include "Renderer.h"

struct VertexBufferElement {
	GLuint type;
	GLuint count;
	GLubyte normalised;

	static GLuint getSizeOfType(GLuint type){
		switch(type) {
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements;
	GLuint m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0) { };

	template<typename T>
	void push(unsigned int count) {
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count) {
		m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	template<>
	void push<GLuint>(unsigned int count) {
		m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void push<GLubyte>(unsigned int count) {
		m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement>& getElements() const { return m_Elements; }
	inline unsigned int getStride() const { return m_Stride; }

};
