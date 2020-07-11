#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* window;
bool running = false;

bool initGLFW() {
	if(!glfwInit())
		return false;

	window = glfwCreateWindow(1280, 720, "Audio Engine", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
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

void render() {
	glClear(GL_COLOR_BUFFER_BIT);


	glfwSwapBuffers(window);
}

int main() {

	if(initALL())
		running = true;

	while(!glfwWindowShouldClose(window) && running) {
		
		update();

		render();

		glfwPollEvents();

	}


	return 0;
}