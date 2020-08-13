#include "Shader.h"

unsigned int Shader::createShader(const std::string & vertexShader, const std::string & fragShader) {
	unsigned int program = glCreateProgram();
	GLuint vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


unsigned int Shader::compileShader(unsigned int type, const std::string & source) {
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// get compile status
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	// If compile failed the print out error
	if(result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*) alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

void Shader::readfromFile() {
}

ShaderProgramSource Shader::parseShader(const std::string & filepath) {
	std::ifstream stream(filepath);

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while(getline(stream, line)) {
		if(line.find("#shader") != std::string::npos) {
			if(line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if(line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;

		}
		else {
			ss[(int)type] << line << '\n';
		}
	}

	return {ss[0].str(), ss[1].str()};
}
