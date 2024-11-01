#pragma once

#include <GL/glew.h>

#include <iostream>
#include <vector>
#include <fstream>

class Texture
{
public:
	Texture(const char *filename, int width, int height, int bitdepth);
	Texture(const char *filename);
	~Texture();

	bool LoadTexture(); // Load texture from file
	//bool LoadTextureA(); // Load texture from file with alpha channel
	void UseTexture();
	void ClearTexture();
private:
	GLuint textureID;
	int width, height, bitDepth;

	std::vector<unsigned char> data;

	const char* fileLocation;

	bool LoadBMP();
	bool LoadPNG();

	void ConvertBitDepth();
};

