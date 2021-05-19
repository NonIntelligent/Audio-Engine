#pragma once

#include "Components.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexObjects.h"
#include "Maths/WorldMaths.h"

struct Entity {
	int entityMask;

	std::vector<Component*> components;
};

// Generic object class for all objects
class GameObject {
private:
	// Unused. Maybe implemented in the far future.
	unsigned int objectID = 0;

public:
	Vec3f position;
	Vec3f rotationAngles;
	Vec3f scale{1.0, 1.0, 1.0};

	bool usePhysics = false;
public:
	virtual void init() = 0;
	virtual void update(double dt) = 0;

	GameObject() {};
	// Virtual so that deleting a GameObject will instead use the latest child's deconstructor.
	virtual ~GameObject() {};

	// Set the id of this gameObject. Currently serves no purpose right now.
	inline void setID(unsigned int id) {
		objectID = id;
	};
	inline unsigned int getID() const {
		return objectID;
	};

};

// Abstract Model Propagates GameObject virtual methods
class Model : public GameObject {
protected:
	bool setup = false;
	bool hasIndexBuffer = false;
	virtual void setupRendering() = 0;

public:

	bool useCollision = false;

	VertexArray* va;
	VertexBuffer* vb;
	IndexBuffer* ib;

	std::string shaderName;
	std::vector<ShaderUniform> uniforms;

	Vec4f colour;
	Mat4f modelMatrix;

public:
	Model();
	~Model();

	inline unsigned int isIndexBuffer() const {
		return hasIndexBuffer;
	};

};

