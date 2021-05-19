#include "Primitive.h"

void Cube::setupRendering() {
	va = new VertexArray();

	// Use this buffer
	// Specify the data to use and its layout (x = vertecies * no. of components xyz)
	vb = new VertexBuffer(cubeVertices, 24 * 8 * sizeof(float), 24, GL_STATIC_DRAW);

	// Bind attributes to vertex buffer and array
	VertexBufferLayout layout;
	// Vertex has 8 (3 coordinate 3 normal 2 texture) components and are all floats
	layout.push<float>(3); // position
	layout.push<float>(3); // normal
	layout.push<float>(2); // texCoord
	va->addBuffer((*vb), layout);

	// Using index buffer saves 27% of bytes (1680 / 2304).
	// 1680 bytes at 24 vertices and 36 indices. 2304 bytes at 36 vertices and 0 indices.

	ib = new IndexBuffer(indices, 36, GL_STATIC_DRAW);
	hasIndexBuffer = true;

	shaderName = "Player";

	Vec3f temp = Vec3f(1.f, 1.f, 1.f);

	ShaderUniform u_Colour;
	u_Colour.name = "u_Colour";
	u_Colour.dataMatrix.setRowData(0, colour);
	u_Colour.type = UniformType::VEC3;
	ShaderUniform textureSlot;
	textureSlot.name = "u_Texture";
	textureSlot.resourceName = "box";
	textureSlot.dataMatrix.matrix[0][0] = 1.f;
	textureSlot.type = UniformType::TEXTURE;
	ShaderUniform model;
	model.name = "u_model";
	model.dataMatrix = modelMatrix;
	model.type = UniformType::MAT4;


	uniforms.push_back(u_Colour);
	//uniforms.push_back(textureSlot);
	uniforms.push_back(model);
}

Cube::Cube(Vec3f pos) {
	position = pos;
	colour.set(0.8f, 0.f, 0.6f, 1.f);
	scale.set(1.f, 1.f, 1.f);
}

void Cube::init() {
	setupRendering();

	setup = true;
}

void Cube::update(double dt) {

	// Scale, then rotate and finally translate
	Mat4f::scaleVec(modelMatrix, scale);
	Mat4f::rotate(modelMatrix, Vec3f(1.f, 1.f, 1.f), rotationAngles);
	Mat4f::translate(modelMatrix, position);

	// updates uniforms
	uniforms.at(0).dataMatrix.setRowData(0, colour);
	uniforms.at(1).dataMatrix = modelMatrix;

	// Reset values.
	modelMatrix.setAsIdentity(); // Remove this to apply transform every update
}
