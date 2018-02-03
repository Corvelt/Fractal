#include "FractalCreator.h"
#include <assert.h>



FractalCreator::FractalCreator(int width, int height): m_width(width), m_height(height),
m_histogram(new int[Mandelbrot::MAX_IT]), m_fractal(new int[m_width*m_height]), m_bitmap(m_width, m_height),
m_zoomList(m_width, m_height)
{
	for (int i = 0; i < Mandelbrot::MAX_IT; i++)
	{
		m_histogram[i] = 0;
	}
	for (int i = 0; i < m_width*m_height; i++)
	{
		m_fractal[i] = 0;
	}

	m_zoomList.Add(zoom(m_width / 2, m_height / 2, 4.0 / m_width));
	m_zoomList.Add(zoom(295, m_height - 202, 0.1));
//	m_zoomList.Add(zoom(312, m_height - 304, 0.1));
//	m_zoomList.Add(zoom(582, m_height - 355, .1));
//	m_zoomList.Add(zoom(393, m_height - 312, .1));
}

void FractalCreator::AddColorRange(double rangeEnd, const RGB& rgb)
{
	m_ranges.push_back(rangeEnd*Mandelbrot::MAX_IT);
	m_colors.push_back(rgb);

	if (m_bGotFirstRange)
	{
		m_rangeTotals.push_back(0);
	}

	m_bGotFirstRange = true;
}

void FractalCreator::CalculateIterations()
{
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			pair<double, double> coords = m_zoomList.ZoomIn(x, y);
			int iterations = Mandelbrot::GetIterations(coords.first, coords.second);

			m_fractal[y * m_width + x] = iterations;
			if (iterations != Mandelbrot::MAX_IT)
			{
				m_histogram[iterations]++;
			}
		}
	}
}

void FractalCreator::CalculateRangeTotals()
{
	int rangeIndex = 0;
	for (int i = 0; i < Mandelbrot::MAX_IT; i++)
	{
		int pixels = m_histogram[i];		

		if (i > m_ranges[rangeIndex + 1])
		{
			rangeIndex++;
		}

		m_rangeTotals[rangeIndex] += pixels;
	}	
}

int FractalCreator::GetRange(int iterations) const
{
	int range = 0;
	for (int i = 0; i < m_ranges.size(); i++)
	{
		range = i;
		if (m_ranges[i] > iterations)
			break;
	}
	range--;
	assert(range > -1);
	assert(range < m_ranges.size());

	return range;
}

void FractalCreator::CalculateTotalIterations()
{
	for (int i = 0; i < Mandelbrot::MAX_IT; i++)
	{
		m_total += m_histogram[i];
	}
}

void FractalCreator::DrawFractal()
{	
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			int iterations = m_fractal[y * m_width + x];
			int range = GetRange(iterations);
			int rangeTotal = m_rangeTotals[range];
			int rangeStart = m_ranges[range];

			RGB& startColor = m_colors[range];
			RGB& endColor = m_colors[range+1];
			RGB colorDiff = endColor - startColor;

			uint8_t red = 0;
			uint8_t green = 0;
			uint8_t blue = 0;
			
			if (iterations != Mandelbrot::MAX_IT)
			{
				int totalPixels = 0;
				double hue = 0.0;

				for (int i = rangeStart; i <= iterations; i++)
				{
					totalPixels += m_histogram[i];
				}

				red = startColor.r + colorDiff.r * (double)totalPixels/rangeTotal;
				green = startColor.g + colorDiff.g * (double)totalPixels / rangeTotal;
				blue = startColor.b + colorDiff.b * (double)totalPixels / rangeTotal;
			}

			m_bitmap.SetPixel(x, y, red, green, blue);
		}
	}
}

void FractalCreator::WriteBitmap(std::string name)
{
	m_bitmap.Write(name);
}

void FractalCreator::run(string name)
{
	CalculateIterations();
	CalculateTotalIterations();
	CalculateRangeTotals();
	DrawFractal();
	WriteBitmap(name);
}

FractalCreator::~FractalCreator()
{
}
