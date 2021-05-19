#pragma once
#include "Maths/WorldMaths.h"

struct Camera {
	Vec3f pos = {0.0, 0.0, 5.0};
	Vec3f target = {0.0, 0.0, -1.0};
	Vec3f up = {0.0, 1.0, 0.0};

	double fov_y = 90.0;
	float viewport[2] = {1280, 720};
	double near = 0.1;
	double far = 1000.0;

	Camera() {	};
	~Camera() {	};

	Mat4f perspective();
	Mat4f lookAt();

	void setPos(double x, double y, double z);
	void setTarget();
	void setUp();
	void setViewPort();
};
