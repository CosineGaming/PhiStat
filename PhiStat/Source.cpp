#include <iostream>
#include <math.h>

int square(int x)
{
	return x*x;
}

void graph(int(*function)(int), const int yrows, const int xmax, const int xmin = 0)
{
	int xvalues = xmax - xmin;
	int * results = new int[xvalues];
	int ymin = 100000;
	int ymax = -1 * ymin;
	for (int i = 0; i < xvalues; ++i)
	{
		results[i] = function(i + xmin);
		if (results[i] < ymin)
		{
			ymin = results[i];
		}
		if (results[i] > ymax)
		{
			ymax = results[i];
		}
	}
	int yvalues = ymax - ymin;
	int ylabelwidth = log10(ymax);
	float xscale = xvalues / (float)(78 - ylabelwidth);
	float yscale = yvalues / (float)yrows;
	for (int y = yrows - 1; y >= 0; --y)
	{
		std::cout << int(y*yscale);
		for (int s = 0; s < ylabelwidth - log10(y*yscale); ++s)
		{
			std::cout << " ";
		}
		std::cout << "|";
		for (int x = 0; x < 78 - ylabelwidth; ++x)
		{
			if (results[int(x * xscale)] > y * yscale)
			{
				std::cout << "X";
			}
			else
			{
				std::cout << " ";
			}
		}
	}
}

int main()
{
	graph(square, 50, 60);
}