#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "GL/glew.h"
#include "IO/FileReader.h"

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader {
public:
	
	static unsigned int createShader(const std::string& vertexShader, const std::string& fragShader);
	static void readfromFile();
	static ShaderProgramSource parseShader(const std::string& filepath);

private:

	static unsigned int compileShader(unsigned int type, const std::string& source);

};


enum class ShaderType {
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

