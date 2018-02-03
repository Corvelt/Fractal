#include "Bitmap.h"
#include "BitmapInfoHeader.h"
#include "BitmapFileHeader.h"
#include <fstream>

using namespace std;

Bitmap::Bitmap(int width, int height) : m_width(width), m_height(height), m_pixels(new uint8_t[width * height * 3]{})
{
}

bool Bitmap::Write(string a_filename)
{
	BitMapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;

	fileHeader.fileSize = sizeof(BitMapFileHeader) + sizeof(BitmapInfoHeader) + (m_width * m_height * 3);
	fileHeader.dataOffset = sizeof(BitMapFileHeader) + sizeof(BitmapInfoHeader);

	infoHeader.width = m_width;
	infoHeader.height = m_height;

	ofstream file;
	file.open(a_filename, ios::out | ios::binary);
	if (!file)
	{
		return false;
	}

	file.write((char *)&fileHeader, sizeof(fileHeader));
	file.write((char *)&infoHeader, sizeof(infoHeader));
	file.write((char *)m_pixels.get(), (m_width * m_height * 3));

	file.close();
	if (!file)
	{
		return false;
	}
	return true;
}

void Bitmap::SetPixel(int a_x, int a_y, uint8_t a_red, uint8_t a_green, uint8_t a_blue)
{
	uint8_t *pixel = m_pixels.get();

	pixel += (a_y*3) * m_width + (a_x*3);
	pixel[0] = a_blue;
	pixel[1] = a_green;
	pixel[2] = a_red;
}

Bitmap::~Bitmap()
{
}
