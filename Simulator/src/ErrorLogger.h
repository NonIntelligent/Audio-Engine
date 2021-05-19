#pragma once

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) glClearErrors();\
	x;\
	ASSERT(glCheckError(#x, __FILE__, __LINE__))

void glClearErrors();
bool glCheckError(const char* function, const char* file, int line);

