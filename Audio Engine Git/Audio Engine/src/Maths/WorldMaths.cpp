#include "WorldMaths.h"

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
	result->x = a->y * b->z - b->y * a->z;
	result->y = a->x * b->z - b->x * a->z;
	result->z = a->x * b->y - b->x * a->y;

}

float Vec3f::lengthSquare() {
	return x*x + y*y + z*z;
}


