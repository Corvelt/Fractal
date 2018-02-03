#pragma once

#include <string>
#include <cstdint>
#include <memory>
using namespace std;

class Bitmap
{
private:
	int m_width{0};
	int m_height{0};
	unique_ptr<uint8_t[]> m_pixels{ nullptr };
public:
	Bitmap(int width, int height);
	void SetPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue );
	bool Write(string filename);
	~Bitmap();
};

