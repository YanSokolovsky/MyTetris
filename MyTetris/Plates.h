#pragma once
#include "Squer.h"
#include "ConsoleFunctions.h"

#include <string>
using namespace std;
struct Plate
{
	Squer** f;
	int height;
	bool gameover;
	int width;
};
struct ScorePlate : public Plate
{
	int pointsLine;
	ScorePlate(int w)
	{
		pointsLine = 0;
		height = 5;
		width = w;
		f = new Squer * [5];
		for (int i = 0 ; i < 5; i++)
		{
			f[i] = new Squer[w];
			for (int y = 0; y < w; y++)
			{
				f[i][y].sq = "::";
			}
		}
	}
};
struct Fuild : public Plate
{
	Fuild(int h, int w)
	{
		gameover = false;
		height = h;
		width = w;
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
struct drawerVisitor
{
	int end_of_scorePlate;
	char buffer[5000];
	void get_score_plate(ScorePlate* scorePlate)
	{
		int count = 0;
		string sc = to_string(scorePlate->pointsLine);
		char* scoreline = new char[scorePlate->width * 2];
		int length = (scorePlate->width * 2 - sc.size()) / 2;
		for (int i = 0; i < scorePlate->width * 2; i++)
		{
			buffer[count] = ':';
			count++;
		}
		for (int i = 0; i < sc.size(); i++)
		{
			buffer[length] = sc[length];
			length++;
		}
		buffer[count] = '\n';
		count++;
		for (int i = 0; i < scorePlate->height; i++)
		{
			for (int y = 0; y < scorePlate->width; y++)
			{
				buffer[count] = scorePlate->f[i][y].sq[0];
				buffer[count + 1] = scorePlate->f[i][y].sq[1];
				count += 2;
			}
			buffer[count] = '\n';
			count++;
		}
		end_of_scorePlate = count;
	}
	void get_game_fuild(Fuild* fuild)
	{
		int count = end_of_scorePlate;
		for (int i = 0; i < fuild->height; i++)
		{
			for (int y = 0; y < fuild->width; y++)
			{
				buffer[count] = fuild->f[i][y].sq[0];
				buffer[count + 1] = fuild->f[i][y].sq[1];
				count += 2;
			}
			buffer[count] = '\n';
			count++;
		}
		end_of_scorePlate = count;
	}
	void draw(Fuild* fuild, ScorePlate* scorePlate)
	{
		get_score_plate(scorePlate);
		get_game_fuild(fuild);
		move_cursore_topleft();
		buffer[end_of_scorePlate] = '\0';
		puts(buffer);
	}
};