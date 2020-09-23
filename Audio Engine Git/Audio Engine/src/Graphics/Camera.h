#pragma once
#include "Maths/WorldMaths.h"

struct Camera {
	Vec3f pos = {0.f, 0.f, 5.f};
	Vec3f target = {0.f, 0.f, -1.f};
	Vec3f up = {0.f, 1.f, 0.f};

	double fov_y = 90.0;
	float viewport[2] = {1280, 720};
	float near = 0.1f;
	float far = 1000.f;

	Camera() {	};
	~Camera() {	};

	Mat4f perspective();
	Mat4f lookAt();

	void setPos(float x, float y, float z);
	void setTarget();
	void setUp();
	void setViewPort();
};
