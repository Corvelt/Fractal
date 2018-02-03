#pragma once
class Mandelbrot
{
public:
	static const int MAX_IT = 100;
public:
	Mandelbrot();
	~Mandelbrot();

	static int GetIterations(double x, double y);
};

