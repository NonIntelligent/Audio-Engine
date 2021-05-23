#include <iostream>

#include "AudioReader.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Graphics/Renderer.h"
#include "Graphics/VertexObjects.h"
#include "Graphics/Camera.h"
#include "Graphics/Shader.h"
#include "IO/Keyboard.h"
#include "IO/Mouse.h"
#include "Objects/Objects.h"
#include "Objects/Primitive.h"


GLFWwindow* window;
Camera camera;
Renderer* renderer;
Mouse mouse;
bool running = false;
bool noClipToggle = true;
bool debug = false;

std::vector<GameObject*> objects;

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

	glfwSetKeyCallback(window, Keyboard::key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

	// Init objects here
	renderer = new Renderer();
	renderer->init();

	Cube* cube1 = new Cube({0.0, 0.0, -2.0});

	objects.push_back(cube1);

	for(int i = 0; i < objects.size(); i++) {
		objects.at(i)->init();
	}

	return true;
}

void update(double timestep) {
	const float radius = 50.f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;

	float r = sin(glfwGetTime());
	float g = (cos(glfwGetTime()) + 1) * 2;
	float b = sin(glfwGetTime()) * 2;

	for(int i = 0; i < objects.size(); i++) {
		objects.at(i)->update(timestep);
	}

	renderer->update(timestep);

	//camera.setPos(camX, 0.f, camZ);

}

void render(double interpolate) {
	renderer->clear();
	renderer->perspective();
	renderer->lookAt();
	renderer->updateCameraUniform();

	for(auto it = objects.begin(); it != objects.end(); it++) {

		Model* model = dynamic_cast<Model*>((*it));

		// Skip if object is not a model
		if(model == nullptr) {
			continue;
		}

		renderer->draw(model, model->shaderName);
	}

	glfwSwapBuffers(window);
}

void updateKeyboardInput(double frameTime) {
	if(Keyboard::getKeyState(GLFW_KEY_H) == KeyState::JUST_PRESSED) {
		// XOR operation to toggle a bit (toggle true and false).
		debug ^= true;
	}

	if(Keyboard::getKeyState(GLFW_KEY_LEFT_ALT) == KeyState::JUST_PRESSED) {
		// Enables free mouse.
		mouse.freeMouse = true;
		mouse.mouseOffsetX = 0;
		mouse.mouseOffsetY = 0;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	if(Keyboard::getKeyState(GLFW_KEY_LEFT_ALT) == KeyState::JUST_RELEASED) {
		// Disables free mouse.
		glfwGetCursorPos(window, &mouse.mouseX, &mouse.mouseY);
		mouse.lastMouseX = mouse.mouseX;
		mouse.lastMouseY = mouse.mouseY;
		mouse.freeMouse = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}


	if(Keyboard::getKeyState(GLFW_KEY_W) == KeyState::JUST_PRESSED) {
		if(noClipToggle) {
			renderer->camSpeedZ = -4.f;
		}
	}
	if(Keyboard::getKeyState(GLFW_KEY_S) == KeyState::JUST_PRESSED) {
		if(noClipToggle) {
			renderer->camSpeedZ = 4.f;
		}
	}
	if(Keyboard::getKeyState(GLFW_KEY_A) == KeyState::JUST_PRESSED) {
		if(noClipToggle) {
			renderer->camSpeedX = -4.f;
		}
	}
	if(Keyboard::getKeyState(GLFW_KEY_D) == KeyState::JUST_PRESSED) {
		if(noClipToggle) {
			renderer->camSpeedX = 4.f;
		}
	}

	if(Keyboard::getKeyState(GLFW_KEY_SPACE) == KeyState::JUST_PRESSED) {
		if(noClipToggle) {
			renderer->camSpeedY = 4.f;
		}
	}
	if(Keyboard::getKeyState(GLFW_KEY_LEFT_CONTROL) == KeyState::JUST_PRESSED) {
		if(noClipToggle) {
			renderer->camSpeedY = -4.f;
		}
	}

	if(Keyboard::getKeyState(GLFW_KEY_W) == KeyState::JUST_RELEASED) {
		if(noClipToggle) {
			Keyboard::getKeyState(GLFW_KEY_S) == KeyState::JUST_PRESSED ? renderer->camSpeedZ = 1.f : renderer->camSpeedZ = 0.f;
		}
	}
	if(Keyboard::getKeyState(GLFW_KEY_S) == KeyState::JUST_RELEASED) {
		if(noClipToggle) {
			Keyboard::getKeyState(GLFW_KEY_W) == KeyState::JUST_PRESSED ? renderer->camSpeedZ = -1.f : renderer->camSpeedZ = 0.f;
		}
	}
	if(Keyboard::getKeyState(GLFW_KEY_A) == KeyState::JUST_RELEASED) {
		if(noClipToggle) {
			Keyboard::getKeyState(GLFW_KEY_D) == KeyState::JUST_PRESSED ? renderer->camSpeedX = 1.f : renderer->camSpeedX = 0.f;
		}
	}
	if(Keyboard::getKeyState(GLFW_KEY_D) == KeyState::JUST_RELEASED) {
		if(noClipToggle) {
			Keyboard::getKeyState(GLFW_KEY_A) == KeyState::JUST_PRESSED ? renderer->camSpeedX = -1.f : renderer->camSpeedX = 0.f;
		}
	}
	if(Keyboard::getKeyState(GLFW_KEY_SPACE) == KeyState::JUST_RELEASED) {
		if(noClipToggle) {
			Keyboard::getKeyState(GLFW_KEY_LEFT_CONTROL) == KeyState::JUST_PRESSED ? renderer->camSpeedY = -1.f : renderer->camSpeedY = 0.f;
		}
	}
	if(Keyboard::getKeyState(GLFW_KEY_LEFT_CONTROL) == KeyState::JUST_RELEASED) {
		if(noClipToggle) {
			Keyboard::getKeyState(GLFW_KEY_SPACE) == KeyState::JUST_PRESSED ? renderer->camSpeedY = 1.f : renderer->camSpeedY = 0.f;
		}
	}

	Keyboard::updateKeyStates();
}

void updateMouseInput(double dt) {
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if(noClipToggle && state == GLFW_PRESS && mouse.currentDelay <= 0) {
		/*Sphere* sphere = new Sphere(renderer->camPos);
		sphere->init();
		Vec3f::scale(&sphere->phys.velocity, &renderer->camTargetDir, 24.f);
		objects.push_back(sphere);
		mouse.currentDelay = mouse.clickTickDelay;*/
	}

	if(mouse.freeMouse) return;

	if(!noClipToggle) return;

	glfwGetCursorPos(window, &mouse.mouseX, &mouse.mouseY);

	if(mouse.firstMouse) {
		mouse.lastMouseX = mouse.mouseX;
		mouse.lastMouseY = mouse.mouseY;
		mouse.firstMouse = false;
	}

	// Calc offsets. Y is inverted due to different coordinate spaces.
	mouse.mouseOffsetX = mouse.mouseX - mouse.lastMouseX;
	mouse.mouseOffsetY = mouse.lastMouseY - mouse.mouseY;

	//glfwSetCursorPos(window, renderer->viewport[0] / 2, renderer->viewport[1] / 2);

	mouse.lastMouseX = mouse.mouseX;
	mouse.lastMouseY = mouse.mouseY;

	mouse.currentDelay -= 1;
}

void processInput(double dt) {
	glfwPollEvents();

	updateKeyboardInput(dt);
	updateMouseInput(dt);
	renderer->updateCameraState(mouse.mouseOffsetX, mouse.mouseOffsetY, mouse.mouseSensitivity);
}

void deleteHeapObjects() {
	delete(renderer);

	for(GameObject* elem : objects) {
		delete(elem);
	}

	objects.clear();
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

		processInput(frameTime);

		while(accumulator >= SEC_PER_UPDATE) {
		update(SEC_PER_UPDATE);
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