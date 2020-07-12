#include "Player.h"

Player::Player(float x, float y, float z) {
	this->pos.set(x, y, z);
}

void Player::update() {
	Vec3f::add(&pos, &pos, &vel);
}

void Player::render() {
	VBO = 1;
}

void Player::movement(Vec3f* direction) {
	vel.set(direction->x * speed, direction->y * speed, direction->z * speed);
}
