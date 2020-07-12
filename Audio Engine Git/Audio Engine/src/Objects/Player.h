#pragma once
#include "Maths/WorldMaths.h"
#include "GL/glew.h"

class Player {
public:

	Player() {	};

	Player(float x, float y, float z);

	~Player() {  };

	void update();

	void render();

	void movement(Vec3f* direction);

public:
	
	Vec3f pos;
	Vec3f vel;

	Vec3f bodySize = Vec3f(0.2f, 0.5f , 0.2f);

	const float speed = 0.2f;
	
	GLuint VBO;
	GLuint VAO;
};