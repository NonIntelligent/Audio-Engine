#pragma once
#include "Maths/WorldMaths.h"

struct Camera {
	Vec3d pos = {0.0, 0.0, 5.0};
	Vec3d target = {0.0, 0.0, -1.0};
	Vec3d up = {0.0, 1.0, 0.0};

	double fov_y = 90.0;
	float viewport[2] = {1280, 720};
	double near = 0.1;
	double far = 1000.0;

	Camera() {	};
	~Camera() {	};

	Mat4d perspective();
	Mat4d lookAt();

	void setPos(double x, double y, double z);
	void setTarget();
	void setUp();
	void setViewPort();
};
