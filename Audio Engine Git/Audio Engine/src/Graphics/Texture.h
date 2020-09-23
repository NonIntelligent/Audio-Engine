#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "GL/glew.h"

class Texture {
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot = 0) const; // around 32 slot max
	void unBind() const;
};