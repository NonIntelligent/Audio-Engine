#include "WorldMaths.h"
#include <math.h>

double toRad(double degrees) {
	return (degrees * PI) / 180;
}

float toRadf(float degrees) {
	return (degrees * PI_f) / 180;
}

double toDegrees(double radians) {
	return (radians * 180) / PI;
}

float toDegreesf(float radians) {
	return (radians * 180) / PI_f;
}

void Vec3d::set(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vec3d::add(Vec3d &result, const Vec3d &a, const Vec3d &b) {
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
}

void Vec3d::sub(Vec3d &result, const Vec3d &a, const Vec3d &b) {
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
}

void Vec3d::scale(Vec3d &result, const Vec3d &a, double k) {
	result.x = a.x * k;
	result.y = a.y * k;
	result.z = a.z * k;
}

void Vec3d::increment(Vec3d &result, const Vec3d &a, double k) {
	result.x += a.x * k;
	result.y += a.y * k;
	result.z += a.z * k;
}

float Vec3d::dot(const Vec3d &a, const Vec3d &b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

void Vec3d::cross(Vec3d &result, const Vec3d &a, const Vec3d &b) {
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;

}

void Vec3d::normalise() {
	float magnitude = lengthSquare();

	if(magnitude == 0) return;

	magnitude = sqrtf(magnitude);

	x = x / magnitude;
	y = y / magnitude;
	z = z / magnitude;
}

void Vec3d::negate() {
	x *= -1;
	y *= -1;
	z *= -1;
}

float Vec3d::lengthSquare() const {
	return x * x + y * y + z * z;
}
bool Vec3d::compare(Vec3d &a) const {
	return a.x == x && a.y == y && a.z == z;
}
//////////////////////////////////////////////

void Mat3d::setRowData(int index, const double * array) {
	matrix[index][0] = array[0];
	matrix[index][1] = array[1];
	matrix[index][2] = array[2];
}

void Mat3d::setRowData(int index, const Vec3d &vec) {
	matrix[index][0] = vec.x;
	matrix[index][1] = vec.y;
	matrix[index][2] = vec.z;
}

void Mat3d::setColData(int index, const double* array) {
	matrix[0][index] = array[0];
	matrix[1][index] = array[1];
	matrix[2][index] = array[2];
}

void Mat3d::setColData(int index, const Vec3d &vec) {
	matrix[0][index] = vec.x;
	matrix[1][index] = vec.y;
	matrix[2][index] = vec.z;
}

Vec3d Mat3d::getRowAsVec(int index) const {
	return Vec3d(matrix[index][0], matrix[index][1], matrix[index][2]);
}

Vec3d Mat3d::getColAsVec(int index) const {
	return Vec3d(matrix[0][index], matrix[1][index], matrix[2][index]);
}

void Mat3d::setAsIdentity() {
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;

	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;

	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
}

void Mat3d::setAsZero() {
	matrix[0][0] = 0;
	matrix[0][1] = 0;
	matrix[0][2] = 0;

	matrix[1][0] = 0;
	matrix[1][1] = 0;
	matrix[1][2] = 0;

	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 0;
}

float Mat3d::determinant() const {
	return	matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) -
		matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2]) +
		matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]);
}

void Mat3d::transpose() {
	float temp = matrix[0][1];
	matrix[0][1] = matrix[1][0];
	matrix[1][0] = temp;

	temp = matrix[0][2];
	matrix[0][2] = matrix[2][0];
	matrix[2][0] = temp;

	temp = matrix[1][2];
	matrix[1][2] = matrix[2][1];
	matrix[2][1] = temp;
}

void Mat3d::add(Mat3d &result, const Mat3d &a, const Mat3d &b) {
	result.matrix[0][0] = a.matrix[0][0] + b.matrix[0][0];
	result.matrix[0][1] = a.matrix[0][1] + b.matrix[0][1];
	result.matrix[0][2] = a.matrix[0][2] + b.matrix[0][2];
								 
	result.matrix[1][0] = a.matrix[1][0] + b.matrix[1][0];
	result.matrix[1][1] = a.matrix[1][1] + b.matrix[1][1];
	result.matrix[1][2] = a.matrix[1][2] + b.matrix[1][2];
								 
	result.matrix[2][0] = a.matrix[2][0] + b.matrix[2][0];
	result.matrix[2][1] = a.matrix[2][1] + b.matrix[2][1];
	result.matrix[2][2] = a.matrix[2][2] + b.matrix[2][2];
}

void Mat3d::sub(Mat3d &result, Mat3d &a, Mat3d &b) {
	result.matrix[0][0] = a.matrix[0][0] - b.matrix[0][0];
	result.matrix[0][1] = a.matrix[0][1] - b.matrix[0][1];
	result.matrix[0][2] = a.matrix[0][2] - b.matrix[0][2];

	result.matrix[1][0] = a.matrix[1][0] - b.matrix[1][0];
	result.matrix[1][1] = a.matrix[1][1] - b.matrix[1][1];
	result.matrix[1][2] = a.matrix[1][2] - b.matrix[1][2];

	result.matrix[2][0] = a.matrix[2][0] - b.matrix[2][0];
	result.matrix[2][1] = a.matrix[2][1] - b.matrix[2][1];
	result.matrix[2][2] = a.matrix[2][2] - b.matrix[2][2];
}

void Mat3d::scale(Mat3d &result, const Mat3d &a, float b) {
	result.matrix[0][0] = a.matrix[0][0] * b;
	result.matrix[0][1] = a.matrix[0][1] * b;
	result.matrix[0][2] = a.matrix[0][2] * b;

	result.matrix[1][0] = a.matrix[1][0] * b;
	result.matrix[1][1] = a.matrix[1][1] * b;
	result.matrix[1][2] = a.matrix[1][2] * b;

	result.matrix[2][0] = a.matrix[2][0] * b;
	result.matrix[2][1] = a.matrix[2][1] * b;
	result.matrix[2][2] = a.matrix[2][2] * b;
}

void Mat3d::mult(Mat3d &result, const Mat3d &a, const Mat3d &b) {
	// n^3 amount of individual multiplication n = matrix size
	// 3*3*3 = 27 multiplications total.
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			result.matrix[i][j] = a.matrix[i][0] * b.matrix[0][j]
				+ a.matrix[i][1] * b.matrix[1][j]
				+ a.matrix[i][2] * b.matrix[2][j];
		}
	}
}

void Mat3d::mult(Vec3d &result, const Mat3d &a, const Vec3d &b) {
	// n^2 amount of individual multiplication n = matrix size
	// 3*3 = 9 multiplications total.
	result.x = a.matrix[0][0] * b.x
		+ a.matrix[0][1] * b.y
		+ a.matrix[0][2] * b.z;

	result.y = a.matrix[1][0] * b.x
		+ a.matrix[1][1] * b.y
		+ a.matrix[1][2] * b.z;

	result.z = a.matrix[2][0] * b.x
		+ a.matrix[2][1] * b.y
		+ a.matrix[2][2] * b.z;
}

bool Mat3d::inverse(Mat3d &result, const Mat3d &a) {
	Vec3d tempVec;
	Vec3d c1 = a.getColAsVec(0);
	Vec3d c2 = a.getColAsVec(1);
	Vec3d c3 = a.getColAsVec(2);

	float det = a.determinant();

	if(det == 0) return false;

	Vec3d::cross(tempVec, c2, c3);
	result.setColData(0, tempVec);

	Vec3d::cross(tempVec, c3, c1);
	result.setColData(1, tempVec);

	Vec3d::cross(tempVec, c1, c2);
	result.setColData(2, tempVec);

	result.transpose();

	scale(result, result, 1 / det);
	return true;
}

void Mat3d::rotate(Mat3d &result, const Vec3d &axis, double angle) {
	Mat3d rotation;
	Mat3d copy = Mat3d(result);

	// Bad plaster fix TODO Switch to quaternions
	if(angle == 90.0) angle += 0.02;

	float rads = toRadf(angle);

	const float c = cosf(rads);
	const float s = sinf(rads);

	// Each component in temp contains the axis multiplied by (1 - cos(angle)) for easier handling.
	Vec3d norm = Vec3d(axis);
	norm.normalise();
	Vec3d temp = Vec3d();
	Vec3d::scale(temp, norm, 1.f - c);

	// Fill out rotation matrix to rotate by xyz axis at once.

	rotation.matrix[0][0] = c + temp.x * norm.x;
	rotation.matrix[0][1] = norm.x * temp.y - norm.z * s;
	rotation.matrix[0][2] = norm.x * temp.z + norm.y * s;

	rotation.matrix[1][0] = norm.y * temp.x + norm.z * s;
	rotation.matrix[1][1] = c + temp.y * norm.y;
	rotation.matrix[1][2] = norm.y * temp.z - norm.x * s;

	rotation.matrix[2][0] = norm.z * temp.x - norm.y * s;
	rotation.matrix[2][1] = norm.z * temp.y + norm.x * s;
	rotation.matrix[2][2] = c + temp.z * norm.z;

	Mat3d::mult(result, rotation, copy);
}

void Mat3d::rotate(Mat3d &result, const Vec3d &axis, const Vec3d &angles) {
	Vec3d x = {axis.x, 0.f, 0.f};
	Vec3d y = {0.f, axis.y, 0.f};
	Vec3d z = {0.f, 0.f, axis.z};

	Mat3d::rotate(result, x, angles.x);
	Mat3d::rotate(result, y, angles.y);
	Mat3d::rotate(result, z, angles.z);
}

///////////////////////////////////////////////////

void Vec4d::set(double x, double y, double z, double w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Vec4d::add(Vec4d &result, const Vec4d &a, const Vec4d &b) {
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
}

void Vec4d::sub(Vec4d &result, const Vec4d &a, const Vec4d &b) {
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
}

void Vec4d::scale(Vec4d &result, const Vec4d &a, float k) {
	result.x = a.x * k;
	result.y = a.y * k;
	result.z = a.z * k;
	result.w = a.w * k;
}

void Vec4d::increment(Vec4d &result, const Vec4d &a, float k) {
	result.x += a.x * k;
	result.y += a.y * k;
	result.z += a.z * k;
	result.w += a.w * k;
}

float Vec4d::dot(const Vec4d &a, const Vec4d &b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

void Vec4d::normalise() {
	float magnitude = lengthSquare();

	if(magnitude == 0) return;

	magnitude = sqrtf(magnitude);

	x = x / magnitude;
	y = y / magnitude;
	z = z / magnitude;
	w = w / magnitude;
}

void Vec4d::negate() {
	x *= -1;
	y *= -1;
	z *= -1;
	w *= -1;
}

float Vec4d::lengthSquare() const {
	return x * x + y * y + z * z + w * w;
}

bool Vec4d::compare(const Vec4d &a) const {
	return a.x == x && a.y == y && a.z == z && a.w == w;
}

//////////////////////////////////

void Mat4d::setRowData(int index, const double * array) {
	matrix[index][0] = array[0];
	matrix[index][1] = array[1];
	matrix[index][2] = array[2];
	matrix[index][3] = array[3];
}

void Mat4d::setRowData(int index, const Vec4d &vec) {
	matrix[index][0] = vec.x;
	matrix[index][1] = vec.y;
	matrix[index][2] = vec.z;
	matrix[index][3] = vec.w;
}

void Mat4d::setRowData(int index, const Vec3d &vec) {
	matrix[index][0] = vec.x;
	matrix[index][1] = vec.y;
	matrix[index][2] = vec.z;
}

void Mat4d::setColData(int index, const double * array) {
	matrix[0][index] = array[0];
	matrix[1][index] = array[1];
	matrix[2][index] = array[2];
	matrix[2][index] = array[3];
}

void Mat4d::setColData(int index, const Vec4d &vec) {
	matrix[0][index] = vec.x;
	matrix[1][index] = vec.y;
	matrix[2][index] = vec.z;
	matrix[3][index] = vec.w;
}

void Mat4d::setColData(int index, const Vec3d &vec) {
	matrix[0][index] = vec.x;
	matrix[1][index] = vec.y;
	matrix[2][index] = vec.z;
}

Vec3d Mat4d::getRowAsVec3(int index) const {
	return Vec3d(matrix[index][0], matrix[index][1], matrix[index][2]);
}

Vec4d Mat4d::getRowAsVec4(int index) const {
	return Vec4d(matrix[index][0], matrix[index][1], matrix[index][2], matrix[index][3]);
}

Vec3d Mat4d::getColAsVec3(int index) const {
	return Vec3d(matrix[0][index], matrix[1][index], matrix[2][index]);
}

Vec4d Mat4d::getColAsVec4(int index) const {
	return Vec4d(matrix[0][index], matrix[1][index], matrix[2][index], matrix[3][index]);
}

Mat3d Mat4d::get3x3Matrix(int row, int col) const {
	Mat3d mat;
	double arr[3];
	int count = 0;
	int row3x3 = 0;

	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++) {
			if(r != row && c != col) {
				arr[count] = matrix[r][c];
				count++;
			}
		}
		if(count == 3) {
			mat.setRowData(row3x3, arr);
			row3x3++;
			count = 0;
		}
	}

	return mat;
}

void Mat4d::setAsIdentity() {
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[0][3] = 0;

	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[1][3] = 0;

	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
	matrix[2][3] = 0;

	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
}

void Mat4d::setAsZero() {
	matrix[0][0] = 0;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[0][3] = 0;

	matrix[1][0] = 0;
	matrix[1][1] = 0;
	matrix[1][2] = 0;
	matrix[1][3] = 0;

	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 0;
	matrix[2][3] = 0;

	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 0;
}

float Mat4d::determinant() const {
	Mat3d mat1 = get3x3Matrix(0, 0);
	Mat3d mat2 = get3x3Matrix(0, 1);
	Mat3d mat3 = get3x3Matrix(0, 2);
	Mat3d mat4 = get3x3Matrix(0, 3);

	float det1 = mat1.determinant();
	float det2 = mat2.determinant();
	float det3 = mat3.determinant();
	float det4 = mat4.determinant();

	return matrix[0][0] * det1 - matrix[0][1] * det2 + matrix[0][2] * det3 - matrix[0][3] * det4;
}

void Mat4d::transpose() {
	float temp = matrix[0][1];
	matrix[0][1] = matrix[1][0];
	matrix[1][0] = temp;

	temp = matrix[0][2];
	matrix[0][2] = matrix[2][0];
	matrix[2][0] = temp;

	temp = matrix[0][3];
	matrix[0][3] = matrix[3][0];
	matrix[3][0] = temp;

	temp = matrix[1][2];
	matrix[1][2] = matrix[2][1];
	matrix[2][1] = temp;

	temp = matrix[1][3];
	matrix[1][3] = matrix[3][1];
	matrix[3][1] = temp;

	temp = matrix[2][3];
	matrix[2][3] = matrix[3][2];
	matrix[3][2] = temp;
}

void Mat4d::data(double arr[16]) const {

	for(int i = 0; i < 16; i++) {
		arr[i] = matrix[i / 4][i % 4];
	}
}

void Mat4d::dataColMaj(double arr[16]) const {

	for(int i = 0; i < 16; i++) {
		arr[i] = matrix[i % 4][i / 4];
	}

}

void Mat4d::add(Mat4d &result, const Mat4d &a, const Mat4d &b) {
	result.matrix[0][0] = a.matrix[0][0] + b.matrix[0][0];
	result.matrix[0][1] = a.matrix[0][1] + b.matrix[0][1];
	result.matrix[0][2] = a.matrix[0][2] + b.matrix[0][2];
	result.matrix[0][3] = a.matrix[0][3] + b.matrix[0][3];

	result.matrix[1][0] = a.matrix[1][0] + b.matrix[1][0];
	result.matrix[1][1] = a.matrix[1][1] + b.matrix[1][1];
	result.matrix[1][2] = a.matrix[1][2] + b.matrix[1][2];
	result.matrix[1][3] = a.matrix[1][3] + b.matrix[1][3];

	result.matrix[2][0] = a.matrix[2][0] + b.matrix[2][0];
	result.matrix[2][1] = a.matrix[2][1] + b.matrix[2][1];
	result.matrix[2][2] = a.matrix[2][2] + b.matrix[2][2];
	result.matrix[2][3] = a.matrix[2][3] + b.matrix[2][3];

	result.matrix[3][0] = a.matrix[3][0] + b.matrix[3][0];
	result.matrix[3][1] = a.matrix[3][1] + b.matrix[3][1];
	result.matrix[3][2] = a.matrix[3][2] + b.matrix[3][2];
	result.matrix[3][3] = a.matrix[3][3] + b.matrix[3][3];

}

void Mat4d::sub(Mat4d &result, const Mat4d &a, const Mat4d &b) {
	result.matrix[0][0] = a.matrix[0][0] - b.matrix[0][0];
	result.matrix[0][1] = a.matrix[0][1] - b.matrix[0][1];
	result.matrix[0][2] = a.matrix[0][2] - b.matrix[0][2];
	result.matrix[0][3] = a.matrix[0][3] - b.matrix[0][3];

	result.matrix[1][0] = a.matrix[1][0] - b.matrix[1][0];
	result.matrix[1][1] = a.matrix[1][1] - b.matrix[1][1];
	result.matrix[1][2] = a.matrix[1][2] - b.matrix[1][2];
	result.matrix[1][3] = a.matrix[1][3] - b.matrix[1][3];

	result.matrix[2][0] = a.matrix[2][0] - b.matrix[2][0];
	result.matrix[2][1] = a.matrix[2][1] - b.matrix[2][1];
	result.matrix[2][2] = a.matrix[2][2] - b.matrix[2][2];
	result.matrix[2][3] = a.matrix[2][3] - b.matrix[2][3];

	result.matrix[3][0] = a.matrix[3][0] - b.matrix[3][0];
	result.matrix[3][1] = a.matrix[3][1] - b.matrix[3][1];
	result.matrix[3][2] = a.matrix[3][2] - b.matrix[3][2];
	result.matrix[3][3] = a.matrix[3][3] - b.matrix[3][3];
}

void Mat4d::scale(Mat4d &result, const Mat4d &a, double b) {
	result.matrix[0][0] = a.matrix[0][0] * b;
	result.matrix[0][1] = a.matrix[0][1] * b;
	result.matrix[0][2] = a.matrix[0][2] * b;
	result.matrix[0][3] = a.matrix[0][3] * b;

	result.matrix[1][0] = a.matrix[1][0] * b;
	result.matrix[1][1] = a.matrix[1][1] * b;
	result.matrix[1][2] = a.matrix[1][2] * b;
	result.matrix[1][3] = a.matrix[1][3] * b;

	result.matrix[2][0] = a.matrix[2][0] * b;
	result.matrix[2][1] = a.matrix[2][1] * b;
	result.matrix[2][2] = a.matrix[2][2] * b;
	result.matrix[2][3] = a.matrix[2][3] * b;

	result.matrix[3][0] = a.matrix[3][0] * b;
	result.matrix[3][1] = a.matrix[3][1] * b;
	result.matrix[3][2] = a.matrix[3][2] * b;
	result.matrix[3][3] = a.matrix[3][3] * b;
}

void Mat4d::mult(Mat4d &result, const Mat4d &a, const Mat4d &b) {
	// n^3 amount of individual multiplication n = matrix size
	// 4*4*4 = 64 multiplications total.
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			result.matrix[i][j] = a.matrix[i][0] * b.matrix[0][j]
				+ a.matrix[i][1] * b.matrix[1][j]
				+ a.matrix[i][2] * b.matrix[2][j]
				+ a.matrix[i][3] * b.matrix[3][j];
		}
	}
}

void Mat4d::mult(Vec4d &result, const Mat4d &a, const Vec4d &b) {
	// n^2 amount of individual multiplication n = matrix size
	// 4*4 = 16 multiplications total.
	result.x = a.matrix[0][0] * b.x
		+ a.matrix[0][1] * b.y
		+ a.matrix[0][2] * b.z
		+ a.matrix[0][3] * b.w;

	result.y = a.matrix[1][0] * b.x
		+ a.matrix[1][1] * b.y
		+ a.matrix[1][2] * b.z
		+ a.matrix[1][3] * b.w;

	result.z = a.matrix[2][0] * b.x
		+ a.matrix[2][1] * b.y
		+ a.matrix[2][2] * b.z
		+ a.matrix[2][3] * b.w;

	result.w = a.matrix[3][0] * b.x
		+ a.matrix[3][1] * b.y
		+ a.matrix[3][2] * b.z
		+ a.matrix[3][3] * b.w;
}

bool Mat4d::inverse(Mat4d &result, const Mat4d &a) {
	result.matrix[0][0] = a.matrix[1][1] * a.matrix[2][2] * a.matrix[3][3] -
		a.matrix[1][1] * a.matrix[2][3] * a.matrix[3][2] -
		a.matrix[2][1] * a.matrix[1][2] * a.matrix[3][3] +
		a.matrix[2][1] * a.matrix[1][3] * a.matrix[3][2] +
		a.matrix[3][1] * a.matrix[1][2] * a.matrix[2][3] -
		a.matrix[3][1] * a.matrix[1][3] * a.matrix[2][2];

	result.matrix[1][0] = -a.matrix[1][0] * a.matrix[2][1] * a.matrix[3][3] +
		a.matrix[1][0] * a.matrix[2][3] * a.matrix[3][2] +
		a.matrix[2][0] * a.matrix[1][2] * a.matrix[3][3] -
		a.matrix[2][0] * a.matrix[1][3] * a.matrix[3][2] -
		a.matrix[3][0] * a.matrix[1][2] * a.matrix[2][3] +
		a.matrix[3][0] * a.matrix[1][3] * a.matrix[2][2];

	result.matrix[2][0] = a.matrix[1][0] * a.matrix[2][1] * a.matrix[3][3] -
		a.matrix[1][0] * a.matrix[2][3] * a.matrix[3][1] -
		a.matrix[2][0] * a.matrix[1][1] * a.matrix[3][3] +
		a.matrix[2][0] * a.matrix[1][3] * a.matrix[3][1] +
		a.matrix[3][0] * a.matrix[1][1] * a.matrix[2][3] -
		a.matrix[3][0] * a.matrix[1][3] * a.matrix[2][1];

	result.matrix[3][0] = -a.matrix[1][0] * a.matrix[2][1] * a.matrix[3][2] +
		a.matrix[1][0] * a.matrix[2][2] * a.matrix[3][1] +
		a.matrix[2][0] * a.matrix[1][1] * a.matrix[3][2] -
		a.matrix[2][0] * a.matrix[1][2] * a.matrix[3][1] -
		a.matrix[3][0] * a.matrix[1][1] * a.matrix[2][2] +
		a.matrix[3][0] * a.matrix[1][2] * a.matrix[2][1];

	result.matrix[0][1] = -a.matrix[0][1] * a.matrix[2][2] * a.matrix[3][3] +
		a.matrix[0][1] * a.matrix[2][3] * a.matrix[3][2] +
		a.matrix[2][1] * a.matrix[0][2] * a.matrix[3][3] -
		a.matrix[2][1] * a.matrix[0][3] * a.matrix[3][2] -
		a.matrix[3][1] * a.matrix[0][2] * a.matrix[2][3] +
		a.matrix[3][1] * a.matrix[0][3] * a.matrix[2][2];

	result.matrix[1][1] = a.matrix[0][0] * a.matrix[2][2] * a.matrix[3][3] -
		a.matrix[0][0] * a.matrix[2][3] * a.matrix[3][2] -
		a.matrix[2][0] * a.matrix[0][2] * a.matrix[3][3] +
		a.matrix[2][0] * a.matrix[0][3] * a.matrix[3][2] +
		a.matrix[3][0] * a.matrix[0][2] * a.matrix[2][3] -
		a.matrix[3][0] * a.matrix[0][3] * a.matrix[2][2];

	result.matrix[2][1] = -a.matrix[0][0] * a.matrix[2][1] * a.matrix[3][3] +
		a.matrix[0][0] * a.matrix[2][3] * a.matrix[3][1] +
		a.matrix[2][0] * a.matrix[0][1] * a.matrix[3][3] -
		a.matrix[2][0] * a.matrix[0][3] * a.matrix[3][1] -
		a.matrix[3][0] * a.matrix[0][1] * a.matrix[2][3] +
		a.matrix[3][0] * a.matrix[0][3] * a.matrix[2][1];

	result.matrix[3][1] = a.matrix[0][0] * a.matrix[2][1] * a.matrix[3][2] -
		a.matrix[0][0] * a.matrix[2][2] * a.matrix[3][1] -
		a.matrix[2][0] * a.matrix[0][1] * a.matrix[3][2] +
		a.matrix[2][0] * a.matrix[0][2] * a.matrix[3][1] +
		a.matrix[3][0] * a.matrix[0][1] * a.matrix[2][2] -
		a.matrix[3][0] * a.matrix[0][2] * a.matrix[2][1];

	result.matrix[0][2] = a.matrix[0][1] * a.matrix[1][2] * a.matrix[3][3] -
		a.matrix[0][1] * a.matrix[1][3] * a.matrix[3][2] -
		a.matrix[1][1] * a.matrix[0][2] * a.matrix[3][3] +
		a.matrix[1][1] * a.matrix[0][3] * a.matrix[3][2] +
		a.matrix[3][1] * a.matrix[0][2] * a.matrix[1][3] -
		a.matrix[3][1] * a.matrix[0][3] * a.matrix[1][2];

	result.matrix[1][2] = -a.matrix[0][0] * a.matrix[1][2] * a.matrix[3][3] +
		a.matrix[0][0] * a.matrix[1][3] * a.matrix[3][2] +
		a.matrix[1][0] * a.matrix[0][2] * a.matrix[3][3] -
		a.matrix[1][0] * a.matrix[0][3] * a.matrix[3][2] -
		a.matrix[3][0] * a.matrix[0][2] * a.matrix[1][3] +
		a.matrix[3][0] * a.matrix[0][3] * a.matrix[1][2];

	result.matrix[2][2] = a.matrix[0][0] * a.matrix[1][1] * a.matrix[3][3] -
		a.matrix[0][0] * a.matrix[1][3] * a.matrix[3][1] -
		a.matrix[1][0] * a.matrix[0][1] * a.matrix[3][3] +
		a.matrix[1][0] * a.matrix[0][3] * a.matrix[3][1] +
		a.matrix[3][0] * a.matrix[0][1] * a.matrix[1][3] -
		a.matrix[3][0] * a.matrix[0][3] * a.matrix[1][1];

	result.matrix[3][2] = -a.matrix[0][0] * a.matrix[1][1] * a.matrix[3][2] +
		a.matrix[0][0] * a.matrix[1][2] * a.matrix[3][1] +
		a.matrix[1][0] * a.matrix[0][1] * a.matrix[3][2] -
		a.matrix[1][0] * a.matrix[0][2] * a.matrix[3][1] -
		a.matrix[3][0] * a.matrix[0][1] * a.matrix[1][2] +
		a.matrix[3][0] * a.matrix[0][2] * a.matrix[1][1];

	result.matrix[0][3] = -a.matrix[0][1] * a.matrix[1][2] * a.matrix[2][3] +
		a.matrix[0][1] * a.matrix[1][3] * a.matrix[2][2] +
		a.matrix[1][1] * a.matrix[0][2] * a.matrix[2][3] -
		a.matrix[1][1] * a.matrix[0][3] * a.matrix[2][2] -
		a.matrix[2][1] * a.matrix[0][2] * a.matrix[1][3] +
		a.matrix[2][1] * a.matrix[0][3] * a.matrix[1][2];

	result.matrix[1][3] = a.matrix[0][0] * a.matrix[1][2] * a.matrix[2][3] -
		a.matrix[0][0] * a.matrix[1][3] * a.matrix[2][2] -
		a.matrix[1][0] * a.matrix[0][2] * a.matrix[2][3] +
		a.matrix[1][0] * a.matrix[0][3] * a.matrix[2][2] +
		a.matrix[2][0] * a.matrix[0][2] * a.matrix[1][3] -
		a.matrix[2][0] * a.matrix[0][3] * a.matrix[1][2];

	result.matrix[2][3] = -a.matrix[0][0] * a.matrix[1][1] * a.matrix[2][3] +
		a.matrix[0][0] * a.matrix[1][3] * a.matrix[2][1] +
		a.matrix[1][0] * a.matrix[0][1] * a.matrix[2][3] -
		a.matrix[1][0] * a.matrix[0][3] * a.matrix[2][1] -
		a.matrix[2][0] * a.matrix[0][1] * a.matrix[1][3] +
		a.matrix[2][0] * a.matrix[0][3] * a.matrix[1][1];

	result.matrix[3][3] = a.matrix[0][0] * a.matrix[1][1] * a.matrix[2][2] -
		a.matrix[0][0] * a.matrix[1][2] * a.matrix[2][1] -
		a.matrix[1][0] * a.matrix[0][1] * a.matrix[2][2] +
		a.matrix[1][0] * a.matrix[0][2] * a.matrix[2][1] +
		a.matrix[2][0] * a.matrix[0][1] * a.matrix[1][2] -
		a.matrix[2][0] * a.matrix[0][2] * a.matrix[1][1];

	float det = a.matrix[0][0] * result.matrix[0][0] +
		a.matrix[0][1] * result.matrix[1][0] +
		a.matrix[0][2] * result.matrix[2][0] +
		a.matrix[0][3] * result.matrix[3][0];

	if(det == 0) return false;

	det = 1.f / det;

	for(int i = 0; i < 16; i++) {
		result.matrix[i / 4][i % 4] = result.matrix[i / 4][i % 4] * det;
	}

	return true;
}

// https://learnopengl.com/Getting-started/Transformations

void Mat4d::rotate(Mat4d &result, const Vec3d &axis, double angle) {
	Mat4d rotation;
	Mat4d copy = Mat4d(result);

	// Bad plaster fix TODO Switch to quaternions
	if(angle == 90.0) angle += 0.02;

	float rads = toRadf(angle);

	const float c = cosf(rads);
	const float s = sinf(rads);

	// Each component in temp contains the axis multiplied by (1 - cos(angle)) for easier handling.
	Vec3d norm = Vec3d(axis);
	norm.normalise();
	Vec3d temp = Vec3d();
	Vec3d::scale(temp, norm, 1.f - c);

	// Fill out rotation matrix to rotate by xyz axis at once.

	rotation.matrix[0][0] = c + temp.x * norm.x;
	rotation.matrix[0][1] = norm.x * temp.y - norm.z * s;
	rotation.matrix[0][2] = norm.x * temp.z + norm.y * s;

	rotation.matrix[1][0] = norm.y * temp.x + norm.z * s;
	rotation.matrix[1][1] = c + temp.y * norm.y;
	rotation.matrix[1][2] = norm.y * temp.z - norm.x * s;

	rotation.matrix[2][0] = norm.z * temp.x - norm.y * s;
	rotation.matrix[2][1] = norm.z * temp.y + norm.x * s;
	rotation.matrix[2][2] = c + temp.z * norm.z;

	Mat4d::mult(result, rotation, copy);
}

void Mat4d::rotate(Mat4d &result, const Vec3d &axis, const Vec3d &angles) {
	Vec3d x = {axis.x, 0.f, 0.f};
	Vec3d y = {0.f, axis.y, 0.f};
	Vec3d z = {0.f, 0.f, axis.z};

	Mat4d::rotate(result, x, angles.x);
	Mat4d::rotate(result, y, angles.y);
	Mat4d::rotate(result, z, angles.z);
}

void Mat4d::translate(Mat4d &result, const Vec3d &translate) {
	Mat4d translation;
	Mat4d copy = Mat4d(result);
	translation.matrix[0][3] = translate.x;
	translation.matrix[1][3] = translate.y;
	translation.matrix[2][3] = translate.z;

	Mat4d::mult(result, translation, copy);
}

void Mat4d::scaleVec(Mat4d &result, const Vec3d &scalar) {
	Mat4d scale;
	Mat4d copy = Mat4d(result);
	scale.matrix[0][0] = scalar.x;
	scale.matrix[1][1] = scalar.y;
	scale.matrix[2][2] = scalar.z;

	Mat4d::mult(result, scale, copy);
}

