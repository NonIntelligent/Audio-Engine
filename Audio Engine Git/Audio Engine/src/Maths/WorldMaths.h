#pragma once

#include <array>
#include <vector>

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

struct Mat3f {
	float matrix[3][3];

	Mat3f() {};
	Mat3f(const Mat3f* mat);

	~Mat3f() {};

	void setRowData(int index, int* array);
	void setRowData(int index, Vec3f* vec);

	void setColData(int index, int* array);
	void setColData(int index, Vec3f* vec);

	Vec3f getRowAsVec(int index);
	Vec3f getColAsVec(int index);

	void setAsIdentity();
	void setAsZero();
	float determinant();
	void transpose();

	static void add(Mat3f* result, Mat3f* a, Mat3f* b);

	static void sub(Mat3f* result, Mat3f* a, Mat3f* b);

	static void scale(Mat3f* result, Mat3f* a, float b);

	static void mult(Mat3f* result, Mat3f* a, Mat3f* b);

	static bool inverse(Mat3f* result, Mat3f* a);

};

struct Vec4f {
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 1.f;

	Vec4f() {
	};

	Vec4f(float x, float y, float z, float w);
	Vec4f(Vec4f* vector);

	~Vec4f() {
	};

	void set(float x, float y, float z, float w);

	static void add(Vec4f* result, Vec4f* a, Vec4f* b);

	static void sub(Vec4f* result, Vec4f* a, Vec4f* b);

	static void scale(Vec4f* result, Vec4f* a, float k);

	static float dot(Vec4f* a, Vec4f* b);

	static void cross(Vec4f* result, Vec4f* a, Vec4f* b);

	float lengthSquare();


};

struct Mat4f {
	float matrix[4][4];

	Mat4f() {};
	Mat4f(const Mat4f* mat);

	~Mat4f() {};

	void setRowData(int index, int* array);
	void setRowData(int index, Vec4f* vec);
	void setRowData(int index, Vec3f* vec);

	void setColData(int index, int* array);
	void setColData(int index, Vec4f* vec);
	void setColData(int index, Vec3f* vec);

	Vec4f getRowAsVec(int index);
	Vec4f getColAsVec(int index);

	Mat3f get3x3Matrix(int row, int col);

	void setAsIdentity();
	void setAsZero();
	float determinant();
	void transpose();

	static void add(Mat4f* result, Mat4f* a, Mat4f* b);

	static void sub(Mat4f* result, Mat4f* a, Mat4f* b);

	static void scale(Mat4f* result, Mat4f* a, float b);

	static void mult(Mat4f* result, Mat4f* a, Mat4f* b);

	static bool inverse(Mat4f* result, Mat4f* a);

};