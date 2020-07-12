#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Objects/Player.h"

GLFWwindow* window;
Player player = Player(0.1f, 0.0f, 0.1f);
bool running = false;

const int VSYNC_OFF = 0;
const int VSYNC_ON = 1;
const int VSYNC_HALF = 2;


bool initGLFW() {
	if(!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);


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

	return true;
}

void update() {

}

void render(double interpolate) {
	glClear(GL_COLOR_BUFFER_BIT);

	player.render();

	glfwSwapBuffers(window);
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