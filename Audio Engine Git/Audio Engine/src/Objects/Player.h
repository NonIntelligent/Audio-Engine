#pragma once
#include "Maths/WorldMaths.h"
#include "Graphics/Renderer.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"

class Player {
public:

	Player();

	Player(float x, float y, float z);

	~Player();

	void update();

	// Called after OpenGl context is made
	void setupRendering();

	void render(Mat4f* perspective, Mat4f* LookAt);

	void movement(Vec3f* direction);

public:
	
	Vec3f pos;
	Vec3f vel;
	Vec4f colour;

	Vec3f bodySize = Vec3f(0.2f, 0.5f , 0.2f);

	float speed = 0.2f;
	
	VertexArray* va;
	VertexBuffer* vb;
	IndexBuffer* ib;

	GLuint shader = 0;
	GLuint VBO = 0;
	GLuint VAO = 0;
	GLuint IBO = 0;
	GLint u_colourLoc = 0;
	GLint u_modelMatLocation = 0;
	GLint u_prjMatLocation = 0;
	GLint u_viewMatLocation = 0;

private:
	bool setup = false;

	float cuboidVertexs[12] = {
	0.f, 0.f, 0.f,// index 0
	0.2f, 0.f, 0.f,
	0.2f, 0.6f, 0.f,
	0.f, 0.6f, 0.f, // 3
	};

	GLuint indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

};