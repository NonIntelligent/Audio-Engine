#pragma once

struct Vec3f {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vec3f() {	};

	Vec3f(float x, float y, float z);
	Vec3f(Vec3f* vector);

	~Vec3f() {	};

	void set(float x, float y, float z);

	static void add(Vec3f* result, Vec3f* a, Vec3f* b);

	static void sub(Vec3f* result, Vec3f* a, Vec3f* b);

	static void scale(Vec3f* result, Vec3f* a, float k);

	static float dot(Vec3f* a, Vec3f* b);

	static void cross(Vec3f* result, Vec3f* a, Vec3f* b);

	float lengthSquare();


};