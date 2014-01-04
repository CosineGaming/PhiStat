#include <iostream>
#include <math.h>

bool prime(int x)
{
	if (x % 2 == 0)
	{
		return false;
	}
	for (int check = 3; check < sqrt(x); check += 2)
	{
		if (check % x == 0)
		{
			return false;
		}
	}
	return true;
}

bool relativeprime(int a, int b)
{
	if (a % 2 == 0 && b % 2 == 0)
	{
		return false;
	}
	for (int check = 3; check < sqrt(a) && check < sqrt(b); check += 2)
	{
		if (check % a == 0 && check % b == 0)
		{
			return false;
		}
	}
	return true;
}

int phi(int x)
{
	int count = 1;
	for (int check = 2; check < x; ++check)
	{
		if (relativeprime(check, x))
		{
			count++;
		}
	}
	return count;
}

int pqphi(int p, int q)
{
	return (p - 1) * (q - 1);
}

void pqphigraph(const int yrows, const int analyze)
{
	int xvalues = analyze;
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
	int ylabelwidth = log10(ymax) + 1;
	float xscale = xvalues / float(78 - ylabelwidth);
	float yscale = yvalues / float(yrows);
	for (int y = yrows - 1; y >= 0; --y)
	{
		std::cout << int(y*yscale);
		for (int s = 0; s < ylabelwidth - (y == 0 ? 1 : log10(y*yscale) + 1); ++s)
		{
			std::cout << " ";
		}
		std::cout << "]";
		for (int x = 0; x < 79 - ylabelwidth; ++x)
		{
			if (results[int(x * xscale)] > y * yscale)
			{
				std::cout << "|";
			}
			else
			{
				std::cout << " ";
			}
		}
	}
	for (int i = 0; i < 79; ++i)
	{
		std::cout << "-";
	}
	for (int t = 1; t < log10(xmax) + 1; ++t)
	{
		for (int s = 0; s < ylabelwidth + 1; ++s)
		{
			std::cout << " ";
		}
		for (int x = 0; x < 79 - ylabelwidth; ++x)
		{
			int index = int(log10(x * xscale < 1 ? 1 : x * xscale) + 1) - t;
			if (index >= 0)
			{
				std::cout << (int(x * xscale) % int(pow(10, index + 1))) / int(pow(10, index));
			}
			else
			{
				std::cout << " ";
			}
		}
	}
	std::cout << std::endl;
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
	int ylabelwidth = log10(ymax) + 1;
	float xscale = xvalues / float(78 - ylabelwidth);
	float yscale = yvalues / float(yrows);
	for (int y = yrows - 1; y >= 0; --y)
	{
		std::cout << int(y*yscale);
		for (int s = 0; s < ylabelwidth - (y == 0 ? 1 : log10(y*yscale) + 1); ++s)
		{
			std::cout << " ";
		}
		std::cout << "]";
		for (int x = 0; x < 79 - ylabelwidth; ++x)
		{
			if (results[int(x * xscale)] > y * yscale)
			{
				std::cout << "|";
			}
			else
			{
				std::cout << " ";
			}
		}
	}
	for (int i = 0; i < 79; ++i)
	{
		std::cout << "-";
	}
	for (int t = 1; t < log10(xmax) + 1; ++t)
	{
		for (int s = 0; s < ylabelwidth + 1; ++s)
		{
			std::cout << " ";
		}
		for (int x = 0; x < 79 - ylabelwidth; ++x)
		{
			int index = int(log10(x * xscale < 1 ? 1 : x * xscale) + 1) - t;
			if (index >= 0)
			{
				std::cout << (int(x * xscale) % int(pow(10, index + 1))) / int(pow(10, index));
			}
			else
			{
				std::cout << " ";
			}
		}
	}
	std::cout << std::endl;
}

void naturalphislope(int analyze)
{
	int different = 0;
	double * slopes = new double[analyze * 2];
	for (int find = 2; different < analyze * 2; ++find)
	{
		double slope = phi(find) / (double) find;
		bool added = false;
		for (int i = 0; i < different; i += 2)
		{
			if (slope == slopes[i])
			{
				slopes[i + 1] += 1;
				added = true;
			}
		}
		if (!added)
		{
			slopes[different] = slope;
			slopes[different + 1] = 1;
			different += 2;
		}
	}
	double bestslope;
	int bestnum = 0;
	for (int i = 0; i < different; i += 2)
	{
		if (slopes[i + 1] > bestnum)
		{
			bestnum = slopes[i + 1];
			bestslope = slopes[i];
		}
	}
	std::cout << bestslope << " was the most common slope, at " << bestnum * 100 / analyze << " percent of natural phis (2 onward)." << std::endl;
}

void pqphislope(int analyze)
{
	int different = 0;
	double * slopes = new double[analyze * 2];
	for (int p = 3; different < analyze * 2; p += 2)
	{
		for (int q = 3; different < analyze * 2; q += 2)
		{
			if (prime(p) && prime(q))
			{
				double slope = pqphi(p, q) / (double) (p * q);
				bool added = false;
				for (int i = 0; i < different; i += 2)
				{
					if (slope == slopes[i])
					{
						slopes[i + 1] += 1;
						added = true;
					}
				}
				if (!added)
				{
					slopes[different] = slope;
					slopes[different + 1] = 1;
					different += 2;
				}
			}
		}
	}
	double bestslope;
	int bestnum = 0;
	for (int i = 0; i < different; i += 2)
	{
		if (slopes[i + 1] > bestnum)
		{
			bestnum = slopes[i + 1];
			bestslope = slopes[i];
		}
	}
	std::cout << bestslope << " was the most common slope, at " << bestnum * 100 / analyze << " percent of double-prime phis." << std::endl;
}

int main()
{
	std::cout << "Here is a graph of natural phis." << std::endl;
	graph(phi, 50, 120);
	std::cout << "Now the computer will attempt to graph double-prime phis. Where n is not prime, it will return 0." << std::endl;
	graph(pqphigraph, 50, 79);
	std::cout << "The computer is now calculating the most common ratio in natural phis. Please wait a moment." << std::endl;
	naturalphislope(500);
	std::cout << "The computer is now attempting to perform the same calculation on double-prime phis." << std::endl;
	pqphislope(500);
}