#include "WorldMaths.h"

double toRad(double degrees) {
	return (degrees * PI) / 180;
}

double toDegrees(double radians) {
	return (radians * 180) / PI;
}

Vec3f::Vec3f(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3f::Vec3f(Vec3f * vector) {
	this->x = vector->x;
	this->y = vector->y;
	this->z = vector->z;
}

void Vec3f::set(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vec3f::add(Vec3f * result, Vec3f * a, Vec3f * b) {
	result->x = a->x + b->x;
	result->y = a->y + b->y;
	result->z = a->z + b->z;
}

void Vec3f::sub(Vec3f * result, Vec3f * a, Vec3f * b) {
	result->x = a->x - b->x;
	result->y = a->y - b->y;
	result->z = a->z - b->z;
}

void Vec3f::scale(Vec3f * result, Vec3f * a, float k) {
	result->x = a->x * k;
	result->y = a->y * k;
	result->z = a->z * k;
}

float Vec3f::dot(Vec3f * a, Vec3f * b) {
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

void Vec3f::cross(Vec3f * result, Vec3f * a, Vec3f * b) {
	result->x = a->y * b->z - a->z * b->y;
	result->y = a->z * b->x - a->x * b->z;
	result->z = a->x * b->y - a->y * b->x;

}

void Vec3f::normalise() {
	float magnitude = lengthSquare();

	if(magnitude == 0) return;

	magnitude = sqrtf(magnitude);

	x = x / magnitude;
	y = y / magnitude;
	z = z / magnitude;
}

void Vec3f::negate() {
	this->x *= -1;
	this->y *= -1;
	this->z *= -1;
}

float Vec3f::lengthSquare() {
	return x*x + y*y + z*z;
}
//////////////////////////////////////////////

Mat3f::Mat3f(const Mat3f* mat) {
	matrix[0][0] = mat->matrix[0][0];
	matrix[0][1] = mat->matrix[0][1];
	matrix[0][2] = mat->matrix[0][2];

	matrix[1][0] = mat->matrix[1][0];
	matrix[1][1] = mat->matrix[1][1];
	matrix[1][2] = mat->matrix[1][2];

	matrix[2][0] = mat->matrix[2][0];
	matrix[2][1] = mat->matrix[2][1];
	matrix[2][2] = mat->matrix[2][2];
}

void Mat3f::setRowData(int index, float * array) {
	matrix[index][0] = array[0];
	matrix[index][1] = array[1];
	matrix[index][2] = array[2];
}

void Mat3f::setRowData(int index, Vec3f * vec) {
	matrix[index][0] = vec->x;
	matrix[index][1] = vec->y;
	matrix[index][2] = vec->z;
}

void Mat3f::setColData(int index, float * array) {
	matrix[0][index] = array[0];
	matrix[1][index] = array[1];
	matrix[2][index] = array[2];
}

void Mat3f::setColData(int index, Vec3f * vec) {
	matrix[0][index] = vec->x;
	matrix[1][index] = vec->y;
	matrix[2][index] = vec->z;
}

Vec3f Mat3f::getRowAsVec(int index) {
	return Vec3f(matrix[index][0], matrix[index][1], matrix[index][2]);
}

Vec3f Mat3f::getColAsVec(int index) {
	return Vec3f(matrix[0][index], matrix[1][index], matrix[2][index]);
}

void Mat3f::setAsIdentity() {
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

void Mat3f::setAsZero() {
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

float Mat3f::determinant() {
	return	matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) -
			matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2]) +
			matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]);
}

void Mat3f::transpose() {
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

void Mat3f::add(Mat3f* result, Mat3f* a, Mat3f* b) {
	result->matrix[0][0] = a->matrix[0][0] + b->matrix[0][0];
	result->matrix[0][1] = a->matrix[0][1] + b->matrix[0][1];
	result->matrix[0][2] = a->matrix[0][2] + b->matrix[0][2];
	
	result->matrix[1][0] = a->matrix[1][0] + b->matrix[1][0];
	result->matrix[1][1] = a->matrix[1][1] + b->matrix[1][1];
	result->matrix[1][2] = a->matrix[1][2] + b->matrix[1][2];

	result->matrix[2][0] = a->matrix[2][0] + b->matrix[2][0];
	result->matrix[2][1] = a->matrix[2][1] + b->matrix[2][1];
	result->matrix[2][2] = a->matrix[2][2] + b->matrix[2][2];
}

void Mat3f::sub(Mat3f* result, Mat3f* a, Mat3f* b) {
	result->matrix[0][0] = a->matrix[0][0] - b->matrix[0][0];
	result->matrix[0][1] = a->matrix[0][1] - b->matrix[0][1];
	result->matrix[0][2] = a->matrix[0][2] - b->matrix[0][2];

	result->matrix[1][0] = a->matrix[1][0] - b->matrix[1][0];
	result->matrix[1][1] = a->matrix[1][1] - b->matrix[1][1];
	result->matrix[1][2] = a->matrix[1][2] - b->matrix[1][2];

	result->matrix[2][0] = a->matrix[2][0] - b->matrix[2][0];
	result->matrix[2][1] = a->matrix[2][1] - b->matrix[2][1];
	result->matrix[2][2] = a->matrix[2][2] - b->matrix[2][2];
}

void Mat3f::scale(Mat3f* result, Mat3f* a, float b) {
	result->matrix[0][0] = a->matrix[0][0] * b;
	result->matrix[0][1] = a->matrix[0][1] * b;
	result->matrix[0][2] = a->matrix[0][2] * b;
	
	result->matrix[1][0] = a->matrix[1][0] * b;
	result->matrix[1][1] = a->matrix[1][1] * b;
	result->matrix[1][2] = a->matrix[1][2] * b;

	result->matrix[2][0] = a->matrix[2][0] * b;
	result->matrix[2][1] = a->matrix[2][1] * b;
	result->matrix[2][2] = a->matrix[2][2] * b;
}

void Mat3f::mult(Mat3f* result, Mat3f* a, Mat3f* b) {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			result->matrix[i][j] = a->matrix[i][0] * b->matrix[0][j]
								 + a->matrix[i][1] * b->matrix[1][j]
								 + a->matrix[i][2] * b->matrix[2][j];
		}
	}
}

bool Mat3f::inverse(Mat3f* result, Mat3f* a) {
	Vec3f tempVec;
	Vec3f c1 = a->getColAsVec(0);
	Vec3f c2 = a->getColAsVec(1);
	Vec3f c3 = a->getColAsVec(2);

	float det = a->determinant();

	if(det == 0) return false;
	
	Vec3f::cross(&tempVec, &c2, &c3);
	result->setColData(0, &tempVec);

	Vec3f::cross(&tempVec, &c3, &c1);
	result->setColData(1, &tempVec);

	Vec3f::cross(&tempVec, &c1, &c2);
	result->setColData(2, &tempVec);

	result->transpose();

	scale(result, result, 1 / det);
	return true;
}

///////////////////////////////////////////////////

Vec4f::Vec4f(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vec4f::Vec4f(Vec4f * vector) {
	this->x = vector->x;
	this->y = vector->y;
	this->z = vector->z;
	this->w = vector->w;
}

void Vec4f::set(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Vec4f::add(Vec4f * result, Vec4f * a, Vec4f * b) {
	result->x = a->x + b->x;
	result->y = a->y + b->y;
	result->z = a->z + b->z;
	result->w = a->w + b->w;
}

void Vec4f::sub(Vec4f * result, Vec4f * a, Vec4f * b) {
	result->x = a->x - b->x;
	result->y = a->y - b->y;
	result->z = a->z - b->z;
	result->w = a->w - b->w;
}

void Vec4f::scale(Vec4f * result, Vec4f * a, float k) {
	result->x = a->x * k;
	result->y = a->y * k;
	result->z = a->z * k;
	result->w = a->w * k;
}

float Vec4f::dot(Vec4f * a, Vec4f * b) {
	return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

void Vec4f::normalise() {
	float magnitude = lengthSquare();

	if(magnitude == 0) return;

	magnitude = sqrtf(magnitude);

	x = x / magnitude;
	y = y / magnitude;
	z = z / magnitude;
	w = w / magnitude;
}

void Vec4f::negate() {
	this->x *= -1;
	this->y *= -1;
	this->z *= -1;
	this->w *= -1;
}

float Vec4f::lengthSquare() {
	return x*x + y*y + z*z + w*w;
}

//////////////////////////////////

Mat4f::Mat4f(const Mat4f * mat) {
	matrix[0][0] = mat->matrix[0][0];
	matrix[0][1] = mat->matrix[0][1];
	matrix[0][2] = mat->matrix[0][2];
	matrix[0][3] = mat->matrix[0][3];

	matrix[1][0] = mat->matrix[1][0];
	matrix[1][1] = mat->matrix[1][1];
	matrix[1][2] = mat->matrix[1][2];
	matrix[1][3] = mat->matrix[1][3];

	matrix[2][0] = mat->matrix[2][0];
	matrix[2][1] = mat->matrix[2][1];
	matrix[2][2] = mat->matrix[2][2];
	matrix[2][3] = mat->matrix[2][3];

	matrix[3][0] = mat->matrix[3][0];
	matrix[3][1] = mat->matrix[3][1];
	matrix[3][2] = mat->matrix[3][2];
	matrix[3][3] = mat->matrix[3][3];
}

void Mat4f::setRowData(int index, float * array) {
	matrix[index][0] = array[0];
	matrix[index][1] = array[1];
	matrix[index][2] = array[2];
	matrix[index][3] = array[3];
}

void Mat4f::setRowData(int index, Vec4f * vec) {
	matrix[index][0] = vec->x;
	matrix[index][1] = vec->y;
	matrix[index][2] = vec->z;
	matrix[index][3] = vec->w;
}

void Mat4f::setRowData(int index, Vec3f * vec) {
	matrix[index][0] = vec->x;
	matrix[index][1] = vec->y;
	matrix[index][2] = vec->z;
	matrix[index][3] = 0;
}

void Mat4f::setColData(int index, float * array) {
	matrix[0][index] = array[0];
	matrix[1][index] = array[1];
	matrix[2][index] = array[2];
	matrix[2][index] = array[3];
}

void Mat4f::setColData(int index, Vec4f * vec) {
	matrix[0][index] = vec->x;
	matrix[1][index] = vec->y;
	matrix[2][index] = vec->z;
	matrix[3][index] = vec->w;
}

void Mat4f::setColData(int index, Vec3f * vec) {
	matrix[0][index] = vec->x;
	matrix[1][index] = vec->y;
	matrix[2][index] = vec->z;
	matrix[3][index] = 0;
}

Vec4f Mat4f::getRowAsVec(int index) {
	return Vec4f(matrix[index][0], matrix[index][1], matrix[index][2], matrix[index][3]);
}

Vec4f Mat4f::getColAsVec(int index) {
	return Vec4f(matrix[0][index], matrix[1][index], matrix[2][index], matrix[3][index]);
}

Mat3f Mat4f::get3x3Matrix(int row, int col) {
	Mat3f mat;
	float arr[3];
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

void Mat4f::setAsIdentity() {
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

void Mat4f::setAsZero() {
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

float Mat4f::determinant() {
	Mat3f mat1 = get3x3Matrix(0, 0);
	Mat3f mat2 = get3x3Matrix(0, 1);
	Mat3f mat3 = get3x3Matrix(0, 2);
	Mat3f mat4 = get3x3Matrix(0, 3);

	float det1 = mat1.determinant();
	float det2 = mat2.determinant();
	float det3 = mat3.determinant();
	float det4 = mat4.determinant();

	return matrix[0][0] * det1 - matrix[0][1] * det2 + matrix[0][2] * det3 - matrix[0][3] * det4;
}

void Mat4f::transpose() {
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

float* Mat4f::data() {
	float singleMat[16];

	for(int i = 0; i < 16; i++) {
		singleMat[i] = matrix[i / 4][i % 4];
	}

	return singleMat;
}

float* Mat4f::dataColMaj() {
	float singleMat[16];

	for(int i = 0; i < 16; i++) {
		singleMat[i] = matrix[i % 4][i / 4];
	}

	return singleMat;
}

void Mat4f::add(Mat4f * result, Mat4f * a, Mat4f * b) {
	result->matrix[0][0] = a->matrix[0][0] + b->matrix[0][0];
	result->matrix[0][1] = a->matrix[0][1] + b->matrix[0][1];
	result->matrix[0][2] = a->matrix[0][2] + b->matrix[0][2];
	result->matrix[0][3] = a->matrix[0][3] + b->matrix[0][3];

	result->matrix[1][0] = a->matrix[1][0] + b->matrix[1][0];
	result->matrix[1][1] = a->matrix[1][1] + b->matrix[1][1];
	result->matrix[1][2] = a->matrix[1][2] + b->matrix[1][2];
	result->matrix[1][3] = a->matrix[1][3] + b->matrix[1][3];

	result->matrix[2][0] = a->matrix[2][0] + b->matrix[2][0];
	result->matrix[2][1] = a->matrix[2][1] + b->matrix[2][1];
	result->matrix[2][2] = a->matrix[2][2] + b->matrix[2][2];
	result->matrix[2][3] = a->matrix[2][3] + b->matrix[2][3];

	result->matrix[3][0] = a->matrix[3][0] + b->matrix[3][0];
	result->matrix[3][1] = a->matrix[3][1] + b->matrix[3][1];
	result->matrix[3][2] = a->matrix[3][2] + b->matrix[3][2];
	result->matrix[3][3] = a->matrix[3][3] + b->matrix[3][3];

}

void Mat4f::sub(Mat4f * result, Mat4f * a, Mat4f * b) {
	result->matrix[0][0] = a->matrix[0][0] - b->matrix[0][0];
	result->matrix[0][1] = a->matrix[0][1] - b->matrix[0][1];
	result->matrix[0][2] = a->matrix[0][2] - b->matrix[0][2];
	result->matrix[0][3] = a->matrix[0][3] - b->matrix[0][3];

	result->matrix[1][0] = a->matrix[1][0] - b->matrix[1][0];
	result->matrix[1][1] = a->matrix[1][1] - b->matrix[1][1];
	result->matrix[1][2] = a->matrix[1][2] - b->matrix[1][2];
	result->matrix[1][3] = a->matrix[1][3] - b->matrix[1][3];

	result->matrix[2][0] = a->matrix[2][0] - b->matrix[2][0];
	result->matrix[2][1] = a->matrix[2][1] - b->matrix[2][1];
	result->matrix[2][2] = a->matrix[2][2] - b->matrix[2][2];
	result->matrix[2][3] = a->matrix[2][3] - b->matrix[2][3];

	result->matrix[3][0] = a->matrix[3][0] - b->matrix[3][0];
	result->matrix[3][1] = a->matrix[3][1] - b->matrix[3][1];
	result->matrix[3][2] = a->matrix[3][2] - b->matrix[3][2];
	result->matrix[3][3] = a->matrix[3][3] - b->matrix[3][3];
}

void Mat4f::scale(Mat4f * result, Mat4f * a, float b) {
	result->matrix[0][0] = a->matrix[0][0] * b;
	result->matrix[0][1] = a->matrix[0][1] * b;
	result->matrix[0][2] = a->matrix[0][2] * b;
	result->matrix[0][3] = a->matrix[0][3] * b;

	result->matrix[1][0] = a->matrix[1][0] * b;
	result->matrix[1][1] = a->matrix[1][1] * b;
	result->matrix[1][2] = a->matrix[1][2] * b;
	result->matrix[1][3] = a->matrix[1][3] * b;

	result->matrix[2][0] = a->matrix[2][0] * b;
	result->matrix[2][1] = a->matrix[2][1] * b;
	result->matrix[2][2] = a->matrix[2][2] * b;
	result->matrix[2][3] = a->matrix[2][3] * b;

	result->matrix[3][0] = a->matrix[3][0] * b;
	result->matrix[3][1] = a->matrix[3][1] * b;
	result->matrix[3][2] = a->matrix[3][2] * b;
	result->matrix[3][3] = a->matrix[3][3] * b;
}

void Mat4f::mult(Mat4f * result, Mat4f * a, Mat4f * b) {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			result->matrix[i][j] = a->matrix[i][0] * b->matrix[0][j]
				+ a->matrix[i][1] * b->matrix[1][j]
				+ a->matrix[i][2] * b->matrix[2][j]
				+ a->matrix[i][3] * b->matrix[3][j];
		}
	}
}

bool Mat4f::inverse(Mat4f* result, Mat4f* a) {
	result->matrix[0][0] =  a->matrix[1][1] * a->matrix[2][2] * a->matrix[3][3] -
							a->matrix[1][1] * a->matrix[2][3] * a->matrix[3][2] - 
							a->matrix[2][1] * a->matrix[1][2] * a->matrix[3][3] +
							a->matrix[2][1] * a->matrix[1][3] * a->matrix[3][2] +
							a->matrix[3][1] * a->matrix[1][2] * a->matrix[2][3] -
							a->matrix[3][1] * a->matrix[1][3] * a->matrix[2][2];

	result->matrix[1][0] = -a->matrix[1][0] * a->matrix[2][1] * a->matrix[3][3] +
							a->matrix[1][0] * a->matrix[2][3] * a->matrix[3][2] +
							a->matrix[2][0] * a->matrix[1][2] * a->matrix[3][3] -
							a->matrix[2][0] * a->matrix[1][3] * a->matrix[3][2] -
							a->matrix[3][0] * a->matrix[1][2] * a->matrix[2][3] +
							a->matrix[3][0] * a->matrix[1][3] * a->matrix[2][2];

	result->matrix[2][0] =  a->matrix[1][0] * a->matrix[2][1] * a->matrix[3][3] -
							a->matrix[1][0] * a->matrix[2][3] * a->matrix[3][1] -
							a->matrix[2][0] * a->matrix[1][1] * a->matrix[3][3] +
							a->matrix[2][0] * a->matrix[1][3] * a->matrix[3][1] +
							a->matrix[3][0] * a->matrix[1][1] * a->matrix[2][3] -
							a->matrix[3][0] * a->matrix[1][3] * a->matrix[2][1];

	result->matrix[3][0] = -a->matrix[1][0] * a->matrix[2][1] * a->matrix[3][2] +
							a->matrix[1][0] * a->matrix[2][2] * a->matrix[3][1] +
							a->matrix[2][0] * a->matrix[1][1] * a->matrix[3][2] -
							a->matrix[2][0] * a->matrix[1][2] * a->matrix[3][1] -
							a->matrix[3][0] * a->matrix[1][1] * a->matrix[2][2] +
							a->matrix[3][0] * a->matrix[1][2] * a->matrix[2][1];

	result->matrix[0][1] = -a->matrix[0][1] * a->matrix[2][2] * a->matrix[3][3] +
							a->matrix[0][1] * a->matrix[2][3] * a->matrix[3][2] +
							a->matrix[2][1] * a->matrix[0][2] * a->matrix[3][3] -
							a->matrix[2][1] * a->matrix[0][3] * a->matrix[3][2] -
							a->matrix[3][1] * a->matrix[0][2] * a->matrix[2][3] +
							a->matrix[3][1] * a->matrix[0][3] * a->matrix[2][2];

	result->matrix[1][1] =  a->matrix[0][0] * a->matrix[2][2] * a->matrix[3][3] -
							a->matrix[0][0] * a->matrix[2][3] * a->matrix[3][2] -
							a->matrix[2][0] * a->matrix[0][2] * a->matrix[3][3] +
							a->matrix[2][0] * a->matrix[0][3] * a->matrix[3][2] +
							a->matrix[3][0] * a->matrix[0][2] * a->matrix[2][3] -
							a->matrix[3][0] * a->matrix[0][3] * a->matrix[2][2];

	result->matrix[2][1] = -a->matrix[0][0] * a->matrix[2][1] * a->matrix[3][3] +
							a->matrix[0][0] * a->matrix[2][3] * a->matrix[3][1] +
							a->matrix[2][0] * a->matrix[0][1] * a->matrix[3][3] -
							a->matrix[2][0] * a->matrix[0][3] * a->matrix[3][1] -
							a->matrix[3][0] * a->matrix[0][1] * a->matrix[2][3] +
							a->matrix[3][0] * a->matrix[0][3] * a->matrix[2][1];

	result->matrix[3][1] =  a->matrix[0][0] * a->matrix[2][1] * a->matrix[3][2] -
							a->matrix[0][0] * a->matrix[2][2] * a->matrix[3][1] -
							a->matrix[2][0] * a->matrix[0][1] * a->matrix[3][2] +
							a->matrix[2][0] * a->matrix[0][2] * a->matrix[3][1] +
							a->matrix[3][0] * a->matrix[0][1] * a->matrix[2][2] -
							a->matrix[3][0] * a->matrix[0][2] * a->matrix[2][1];

	result->matrix[0][2] =  a->matrix[0][1] * a->matrix[1][2] * a->matrix[3][3] -
							a->matrix[0][1] * a->matrix[1][3] * a->matrix[3][2] -
							a->matrix[1][1] * a->matrix[0][2] * a->matrix[3][3] +
							a->matrix[1][1] * a->matrix[0][3] * a->matrix[3][2] +
							a->matrix[3][1] * a->matrix[0][2] * a->matrix[1][3] -
							a->matrix[3][1] * a->matrix[0][3] * a->matrix[1][2];

	result->matrix[1][2] = -a->matrix[0][0] * a->matrix[1][2] * a->matrix[3][3] +
							a->matrix[0][0] * a->matrix[1][3] * a->matrix[3][2] +
							a->matrix[1][0] * a->matrix[0][2] * a->matrix[3][3] -
							a->matrix[1][0] * a->matrix[0][3] * a->matrix[3][2] -
							a->matrix[3][0] * a->matrix[0][2] * a->matrix[1][3] +
							a->matrix[3][0] * a->matrix[0][3] * a->matrix[1][2];

	result->matrix[2][2] =  a->matrix[0][0] * a->matrix[1][1] * a->matrix[3][3] -
							a->matrix[0][0] * a->matrix[1][3] * a->matrix[3][1] -
							a->matrix[1][0] * a->matrix[0][1] * a->matrix[3][3] +
							a->matrix[1][0] * a->matrix[0][3] * a->matrix[3][1] +
							a->matrix[3][0] * a->matrix[0][1] * a->matrix[1][3] -
							a->matrix[3][0] * a->matrix[0][3] * a->matrix[1][1];

	result->matrix[3][2] = -a->matrix[0][0] * a->matrix[1][1] * a->matrix[3][2] +
							a->matrix[0][0] * a->matrix[1][2] * a->matrix[3][1] +
							a->matrix[1][0] * a->matrix[0][1] * a->matrix[3][2] -
							a->matrix[1][0] * a->matrix[0][2] * a->matrix[3][1] -
							a->matrix[3][0] * a->matrix[0][1] * a->matrix[1][2] +
							a->matrix[3][0] * a->matrix[0][2] * a->matrix[1][1];

	result->matrix[0][3] = -a->matrix[0][1] * a->matrix[1][2] * a->matrix[2][3] +
							a->matrix[0][1] * a->matrix[1][3] * a->matrix[2][2] +
							a->matrix[1][1] * a->matrix[0][2] * a->matrix[2][3] -
							a->matrix[1][1] * a->matrix[0][3] * a->matrix[2][2] -
							a->matrix[2][1] * a->matrix[0][2] * a->matrix[1][3] +
							a->matrix[2][1] * a->matrix[0][3] * a->matrix[1][2];

	result->matrix[1][3] =  a->matrix[0][0] * a->matrix[1][2] * a->matrix[2][3] -
							a->matrix[0][0] * a->matrix[1][3] * a->matrix[2][2] -
							a->matrix[1][0] * a->matrix[0][2] * a->matrix[2][3] +
							a->matrix[1][0] * a->matrix[0][3] * a->matrix[2][2] +
							a->matrix[2][0] * a->matrix[0][2] * a->matrix[1][3] -
							a->matrix[2][0] * a->matrix[0][3] * a->matrix[1][2];

	result->matrix[2][3] = -a->matrix[0][0] * a->matrix[1][1] * a->matrix[2][3] +
							a->matrix[0][0] * a->matrix[1][3] * a->matrix[2][1] +
							a->matrix[1][0] * a->matrix[0][1] * a->matrix[2][3] -
							a->matrix[1][0] * a->matrix[0][3] * a->matrix[2][1] -
							a->matrix[2][0] * a->matrix[0][1] * a->matrix[1][3] +
							a->matrix[2][0] * a->matrix[0][3] * a->matrix[1][1];

	result->matrix[3][3] =  a->matrix[0][0] * a->matrix[1][1] * a->matrix[2][2] -
							a->matrix[0][0] * a->matrix[1][2] * a->matrix[2][1] -
							a->matrix[1][0] * a->matrix[0][1] * a->matrix[2][2] +
							a->matrix[1][0] * a->matrix[0][2] * a->matrix[2][1] +
							a->matrix[2][0] * a->matrix[0][1] * a->matrix[1][2] -
							a->matrix[2][0] * a->matrix[0][2] * a->matrix[1][1];

	float det = a->matrix[0][0] * result->matrix[0][0] +
				a->matrix[0][1] * result->matrix[1][0] +
				a->matrix[0][2] * result->matrix[2][0] +
				a->matrix[0][3] * result->matrix[3][0];

	if(det == 0) return false;

	det = 1.f / det;

	for(int i = 0; i < 16; i++) {
		result->matrix[i / 4][i % 4] = result->matrix[i / 4][i % 4] * det;
	}

	return true;
}

