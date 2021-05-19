#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/VertexObjects.h"
#include "Maths/WorldMaths.h"

struct Component {
	int ComponentType;
};

struct MeshComponent : public Component{
	int ComponentType = 5;

	VertexArray* va;
	VertexBuffer* vb;
	IndexBuffer* ib;

	std::string shaderName;
	std::vector<ShaderUniform> uniforms;

	Vec4f colour;
	Mat4f modelMatrix;
};