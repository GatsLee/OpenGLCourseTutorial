#pragma once

#include <GL/glew.h>

#include <iostream>
#include <vector>
#include "stb_image.h"

class Texture
{
public:
	Texture();
	Texture(const char *filename, int width, int height, int bitdepth);
	Texture(const char *filename);
	~Texture();

	bool LoadTexture();
	bool LoadTextureA();
	void UseTexture();
	void ClearTexture();
private:
	GLuint textureID;
	int width, height, bitDepth;

	std::vector<unsigned char> data;

	const char* fileLocation;
};

