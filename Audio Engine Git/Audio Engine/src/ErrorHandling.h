#pragma once
#include <iostream>

#include "GL/glew.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) ErrorHandler::glClearErrors();\
	x;\
	ASSERT(ErrorHandler::glCheckError(#x, __FILE__, __LINE__))

class ErrorHandler {
public:
	static void glClearErrors() {
		while(glGetError() != GL_NO_ERROR);
	}

	static bool glCheckError(const char* function, const char* file, int line) {
		while(GLenum error = glGetError()) {
			std::cout << "OpenGL Error: [" << error << "]" << function <<
				" " << file << ": " << line << std::endl;
			return false;
		}
		return true;
	}

};
