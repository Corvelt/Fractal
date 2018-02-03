#include <iostream>
#include <conio.h>
#include "FractalCreator.h"

using namespace std;

int main()
{
	const string fileName = "test.bmp";	

	FractalCreator _fc(800, 600);

	_fc.AddColorRange(0.0,RGB(0,0,0));
	_fc.AddColorRange(0.125, RGB(255, 0, 0));
	_fc.AddColorRange(.25, RGB(255, 128, 0));
	_fc.AddColorRange(0.375, RGB(225, 255, 0));
	_fc.AddColorRange(.5, RGB(0, 255, 0));
	_fc.AddColorRange(0.625, RGB(0, 255, 128));
	_fc.AddColorRange(.75, RGB(0, 128, 255));
	_fc.AddColorRange(0.875, RGB(0, 0, 255));	
	_fc.AddColorRange(1.0, RGB(255, 0, 255));

	_fc.run(fileName);
	cout << "Finished..." << '\a'<< endl;	
	_getch();

	return 0;
}