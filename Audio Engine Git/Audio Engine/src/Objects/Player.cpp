#include "Player.h"

Player::Player() {
	this->pos.set(0, 0, 0);
}

Player::Player(float x, float y, float z) {
	this->pos.set(x, y, z);
}

Player::~Player() {
	vb->unBind();
	delete(vb);
	ib->unBind();
	delete(ib);
	va->unBind();
	delete(va);
}

void Player::update() {
	Vec3f::add(&pos, &pos, &vel);
}

void Player::setupRendering() {
	va = new VertexArray();

	//Use this buffer
	// Specify the data to use and its layout (x = vertecies * no. of components)
	vb = new VertexBuffer(cuboidVertexs, 4 * 3 * sizeof(float));

	// Bind attributes to vertex buffer and array
	VertexBufferLayout layout;
	layout.push<float>(3);
	va->addBuffer((*vb), layout);

	ib = new IndexBuffer(indices, 6);

	setup = true;
}

void Player::render(Mat4f* perspective, Mat4f* LookAt) {

	if(!setup) return;

	glUseProgram(shader);

	// Use vertex array object that's already been setup
	va->bind();

	u_colourLoc = glGetUniformLocation(shader, "u_Colour");
	glUniform4f(u_colourLoc, colour.x, colour.y, colour.z, colour.w);
	Mat4f modelIdentity;
	modelIdentity.setAsIdentity();

	u_modelMatLocation = glGetUniformLocation(shader, "u_model");
	u_prjMatLocation = glGetUniformLocation(shader, "u_projection");
	u_viewMatLocation = glGetUniformLocation(shader, "u_view");
	glUniformMatrix4fv(u_modelMatLocation, 1, GL_FALSE, modelIdentity.data());
	glUniformMatrix4fv(u_prjMatLocation, 1, GL_FALSE, perspective->data());
	glUniformMatrix4fv(u_viewMatLocation, 1, GL_FALSE, LookAt->data());

	// Draw array with index buffer
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));


}

void Player::movement(Vec3f* direction) {
	vel.set(direction->x * speed, direction->y * speed, direction->z * speed);
}
