#pragma once


struct Vec3f {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vec3f() {	};

	Vec3f(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	};

	~Vec3f() {	};
};