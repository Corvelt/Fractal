#pragma once
#include <string>
#include "zoom.h"
#include <memory>
#include "Mandelbrot.h"
#include "Bitmap.h"
#include "ZoomList.h"
#include <cstdint>
#include <math.h>
#include "RGB.h"
#include <vector>
#include <iostream>

using namespace std;

class FractalCreator
{
private:
//------Variables----------
	int m_width = 0;
	int m_height = 0;
	unique_ptr<int[]> m_histogram;
	unique_ptr<int[]> m_fractal;
	Bitmap m_bitmap;
	ZoomList m_zoomList;
	int m_total = 0;
	vector<int> m_ranges;
	vector<RGB> m_colors;
	vector<int> m_rangeTotals;

	bool m_bGotFirstRange = false;
	
//-------Functions---------	
	void CalculateIterations();
	void CalculateTotalIterations();
	void DrawFractal();	
	void WriteBitmap(string name);
	int GetRange(int iterations) const;
	
public:
//------Variables----------

//-------Functions---------
	FractalCreator(int width, int height);
	void AddColorRange(double rangeEnd, const RGB& rgb);
	void CalculateRangeTotals();

	void run(string name);
	~FractalCreator();
};

