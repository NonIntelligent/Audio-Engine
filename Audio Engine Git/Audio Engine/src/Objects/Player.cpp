#include "Player.h"

Player::Player() {

}

Player::Player(float x, float y, float z) {
	this->pos.set(x, y, z);
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &IBO);
}

Player::~Player() {
}

void Player::update() {
	Vec3f::add(&pos, &pos, &vel);
}

void Player::render() {
	glUseProgram(shader);

	float cuboidpos[24] = {
		0.f, 0.f, 0.f,// index 0
		0.2f, 0.f, 0.f,
		0.2f, 0.f, -0.2f,
		0.f, 0.f, -0.2f, // 3

		0.f, 0.6f, 0.f, // 4
		0.2f, 0.6f, 0.f,
		0.2f, 0.6f, -0.2f,
		0.f, 0.6f, -0.2f // 7
	};

	GLuint indices[] = {
		0, 1, 2, // Bottom face
		2, 3, 0,
		4, 5, 6, // Top face
		6, 7, 4,
		0, 1, 5, // Front face
		5, 4, 0,
		1, 2, 6, // Right side
		6, 5, 1,
		3, 0, 4, // Left side
		4, 7, 3,
		3, 2, 6, // Back side
		6, 7, 3
	};

	//Use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// Specify the data to use and its layout
	glBufferData(GL_ARRAY_BUFFER, 8 * 3 * sizeof(float), cuboidpos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// Index Buffer data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), indices, GL_STATIC_DRAW);

	// Draw array with index buffer
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);


}

void Player::movement(Vec3f* direction) {
	vel.set(direction->x * speed, direction->y * speed, direction->z * speed);
}
