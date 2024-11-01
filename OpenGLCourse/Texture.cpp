#include "Texture.h"

Texture::Texture(const char* filename, int width, int height, int bitdepth)
{
	fileLocation = filename;
	this->width = width;
	this->height = height;
	this->bitDepth = bitdepth;
}

Texture::Texture(const char* filename)
{
	fileLocation = filename;
	width = 0;
	height = 0;
	bitDepth = 0;
}

Texture::~Texture()
{
	ClearTexture();
}

bool Texture::LoadBMP()
{
	std::ifstream file(fileLocation, std::ios::in | std::ios::binary);
	if (!file)
	{
		std::cout << "Failed to open file: " << fileLocation << std::endl;
		return false;
	}

	unsigned char header[54];
	if (!file.read(reinterpret_cast<char*>(header), sizeof(header)))
	{
		std::cout << "Failed to read header of file: " << fileLocation << std::endl;
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		std::cout << "Invalid BMP file: " << fileLocation << std::endl;
		return false;
	}

	width = *reinterpret_cast<int*>(&header[18]);
	height = *reinterpret_cast<int*>(&header[22]);
	int bitsPerPixel = *reinterpret_cast<short*>(&header[28]);
	if (bitsPerPixel != 24 && bitsPerPixel != 32)
	{
		std::cout << "Invalid bits per pixel value: " << bitsPerPixel << std::endl;
		return false;
	}

	int row_padded = (width * 3 + 3) & (~3);
	data.resize(width * height * 3);

	std::vector<unsigned char> rowData(row_padded);
	for (int i = 0; i < height; i++)
	{
		if (!file.read(reinterpret_cast<char*>(rowData.data()), row_padded))
		{
			std::cout << "Failed to read data of file: " << fileLocation << std::endl;
			return false;
		}
		for (int j = 0; j < width; j++)
		{
			int bmpIndex = j * width;
			int rgbIndex = ((height - i - 1) * width + j) * 3;
			data[rgbIndex] = rowData[bmpIndex + 2];
			data[rgbIndex + 1] = rowData[bmpIndex + 1];
			data[rgbIndex + 2] = rowData[bmpIndex];
		}
	}

	ConvertBitDepth();

	file.close();
	return true;
}

bool Texture::LoadPNG()
{
	//read & parse the png header
	std::ifstream file(fileLocation, std::ios::in | std::ios::binary);
	if (!file)
	{
		std::cout << "Failed to open file: " << fileLocation << std::endl;
		return false;
	}

	unsigned char signature[8];
	if (!file.read(reinterpret_cast<char*>(signature), sizeof(signature)))
	{
		std::cout << "Failed to read signature of file: " << fileLocation << std::endl;
		return false;
	}
	const unsigned char pngSignature[8] = { 137, 'P', 'N', 'G', 13, 10, 26, 10};
	if (std::equal(std::begin(signature), std::end(signature), std::begin(pngSignature)) == false)
	{
		std::cout << "Invalid PNG file: " << fileLocation << std::endl;
		return false;
	}
	// handle png chunks

	// process critical chunks

	// decompress image data

	// apply filter

	// reconstruct pixels

	return true;
}

void Texture::ConvertBitDepth()
{
	if (bitDepth == 8)
	{

	}
	else if (bitDepth == 16)
	{
		std::vector<unsigned char> newData;
		for (size_t i = 0; i < width * height * 3; i++)
		{
			unsigned short red16 = (data[i * 2] << 8) | data[i * 2 + 1];
			unsigned short green16 = (data[i * 2 + 2] << 8) | data[i * 2 + 3];
			unsigned short blue16 = (data[i * 2 + 4] << 8) | data[i * 2 + 5];

			newData[i] = red16 >> 8;
			newData[i + 1] = green16 >> 8;
			newData[i + 2] = blue16 >> 8;
		}

		data = std::move(newData);
	}
}

bool Texture::LoadTexture()
{
	if (!LoadBMP())
	{
		return false;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

void Texture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::ClearTexture()
{
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	data.clear();
	fileLocation = nullptr;
}
