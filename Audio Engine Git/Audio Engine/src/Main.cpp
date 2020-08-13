#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Graphics/Shader.h"
#include "Objects/Player.h"
#include "ErrorHandling.h"


GLFWwindow* window;
Player player;
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

	player = Player(0.1f, 0.0f, 0.1f);

	ShaderProgramSource sources = Shader::parseShader("res/Shaders/Player.shader");

	player.shader = Shader::createShader(sources.vertexSource, sources.fragmentSource);

	return true;
}

void update() {

}

void render(double interpolate) {
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	player.render();

	glfwSwapBuffers(window);
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
			ticks = 0;
			frames = 0;
			t -= 1;
		}

	}

	glfwTerminate();

	return 0;
}