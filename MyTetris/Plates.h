#pragma once
#include "Squer.h"
struct Plate
{
	Squer** f;
	int high;
	int wingth;
};
struct ScorePlate : public Plate
{
	ScorePlate(int h, int w)
	{
		high = h;
		wingth = w;
	}
};
struct Fuild : public Plate
{
	bool gameover;
	Fuild(int h, int w)
	{
		gameover = false;
		high = h;
		wingth = w;
		f = new Squer*[h];
		for (int i = 0; i < h; i++)
		{
			f[i] = new Squer[w];
			for (int b = 0; b < w; b++)
			{
				if (b == 0 || b == w - 1)
				{
					f[i][b] = Squer("..");
					continue;
				}
				if (i == 0 && b < w - 1 && b > 0)
				{
					f[i][b] = Squer("__");
					continue;
				}
				if (i == h - 1 && b < w - 1 && b > 0)
				{
					f[i][b] = Squer("``");
					continue;
				}
				f[i][b] = Squer();
			}
		}
	}
};