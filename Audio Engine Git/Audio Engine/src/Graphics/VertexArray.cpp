#include "VertexArray.h"

#include "Renderer.h"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::addBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout) {
	bind();
	vb.bind();
	const auto& elements = layout.getElements();
	GLuint offset = 0;

	for(GLuint i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, 
			element.normalised,layout.getStride(), (const void*) offset));
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}

}

void VertexArray::bind() const {
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::unBind() const {
	GLCall(glBindVertexArray(0));
}
