#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Graphics/Renderer.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/Camera.h"
#include "Graphics/Shader.h"
#include "Objects/Player.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Vendor/stb_image.h"



GLFWwindow* window;
Player* player;
Camera camera;
bool running = false;

const int VSYNC_OFF = 0;
const int VSYNC_ON = 1;
const int VSYNC_HALF = 2;


bool initGLFW() {
	if(!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(1280, 720, "Audio Engine", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(VSYNC_ON);
	return true;
}

bool initGLEW() {
	if(glewInit() != GLEW_OK) {
		GLenum err = 0;
		glewGetErrorString(err);
		std::cout << err << std::endl;
		return false;
	}

	return true;
}

bool initALL() {

	if(!initGLFW()) {
		std::cout << "GLFW initialisation failed" << std::endl;
		return false;
	}

	if(!initGLEW()) {
		std::cout << "GLEW initialisation failed" << std::endl;
		return false;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	player = new Player(0.1f, 0.0f, 0.1f);
	player->setupRendering();

	ShaderProgramSource sources = Shader::parseShader("res/Shaders/Player.shader");

	player->shader = Shader::createShader(sources.vertexSource, sources.fragmentSource);

	return true;
}

void update() {
	const float radius = 50.f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;

	float r = sin(glfwGetTime());
	float g = (cos(glfwGetTime()) + 1) * 2;
	float b = sin(glfwGetTime()) * 2;

	player->colour.x = r;
	player->colour.y = g;
	player->colour.z = b;

	//camera.setPos(camX, 0.f, camZ);

}

void render(double interpolate) {
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mat4f cameraPerspective = camera.perspective();
	Mat4f cameraLookAt = camera.lookAt();

	player->render(&cameraPerspective, &cameraLookAt);

	glfwSwapBuffers(window);
}

void processInput(GLFWwindow *window, double frameTime) {
	float cameraSpeed = 0.1 * frameTime;
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Vec3f temp;
		Vec3f::scale(&temp, &camera.target, cameraSpeed);
		Vec3f::add(&camera.pos, &camera.pos, &temp);
	} 

	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Vec3f temp;
		Vec3f::scale(&temp, &camera.target, cameraSpeed);
		Vec3f::sub(&camera.pos, &camera.pos, &temp);
	} 

	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Vec3f temp;
		Vec3f::cross(&temp, &camera.target, &camera.up);
		temp.normalise();
		Vec3f::scale(&temp, &temp, cameraSpeed);
		Vec3f::sub(&camera.pos, &camera.pos, &temp);
	}

	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Vec3f temp;
		Vec3f::cross(&temp, &camera.target, &camera.up);
		temp.normalise();
		Vec3f::scale(&temp, &temp, cameraSpeed);
		Vec3f::add(&camera.pos, &camera.pos, &temp);
	}


}

void codeTest() {
	Mat4f mat;
	Mat4f inv;
	Mat3f mat3f;

	Vec4f test = Vec4f(0.f, 3.f, 4.f, 6.f);
	Vec4f test2 = Vec4f(9.f, 4.f, 7.f, 2.f);
	Vec4f test3 = Vec4f(8.f, 1.f, 0.f, 7.f);
	Vec4f test4 = Vec4f(5.f, 6.f, 3.f, 0.f);

	mat.setRowData(0, &test);
	mat.setRowData(1, &test2);
	mat.setRowData(2, &test3);
	mat.setRowData(3, &test4);

	for(int i = 0; i < 4; i++) {
		std::cout << mat.matrix[i][0] << "  ";
		std::cout << mat.matrix[i][1] << "  ";
		std::cout << mat.matrix[i][2] << "  ";
		std::cout << mat.matrix[i][3] << "\n";
	}

	std::cout << "/////////////////////" << std::endl;

	Mat4f::inverse(&inv, &mat);

	for(int i = 0; i < 4; i++) {
		std::cout << inv.matrix[i][0] << "  ";
		std::cout << inv.matrix[i][1] << "  ";
		std::cout << inv.matrix[i][2] << "  ";
		std::cout << inv.matrix[i][3] << "\n";
	}

}

void deleteHeapObjects() {
	delete(player);
}

int main() {

	if(initALL())
		running = true;

	double t = 0.0;
	double SEC_PER_UPDATE = 1.0 / 60.0;

	int ups = 0;
	int fps = 0;
	int ticks = 0;
	int frames = 0;

	codeTest();

	// returns time in seconds after glfw initialisation
	double previousTime = glfwGetTime();
	double accumulator = 0.0;

	while(!glfwWindowShouldClose(window) && running) {
		double currentTime = glfwGetTime();
		double frameTime = currentTime - previousTime;
		if(frameTime > 0.33) // If behind by 20+ updates out of 60
			frameTime = 0.33;
		previousTime = currentTime;

		accumulator += frameTime;

		processInput(window, frameTime);

		while(accumulator >= SEC_PER_UPDATE) {
		update();
		ticks++;
		t += SEC_PER_UPDATE;
		accumulator -= SEC_PER_UPDATE;
		}

		render(accumulator / SEC_PER_UPDATE);
		frames++;

		glfwPollEvents();

		if(t > 1) {
			ups = ticks;
			fps = frames;
			std::cout << "ups: " << ups << " fps: " << fps << std::endl;
			std::cout << "Camera Pos " << camera.pos.x << ", " << camera.pos.y << ", " << camera.pos.z << std::endl;
			ticks = 0;
			frames = 0;
			t -= 1;
		}

	}
	
	deleteHeapObjects();
	glfwTerminate();

	return 0;
}