#pragma once
#include "Squer.h"
#include "ConsoleFunctions.h"

#include <string>
using namespace std;

struct ScorePlate;
struct Fuild;
struct Visitor
{
	virtual void get_plate(Fuild* fuild) = 0;
	virtual void get_plate(ScorePlate* scorePlate) = 0;
};
struct Plate
{
	Squer** f;
	int height;
	bool gameover;
	int width;
	int pointsLine;
	virtual void get_drawed(Visitor* dv) = 0;
};
struct ScorePlate : public Plate
{
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
				f[i][y].sq = ".`";
			}
		}
	}
	void clearing_plate()
	{
		for (int i = 0; i < 5; i++)
		{
			for (int y = 0; y < width; y++)
			{
				f[i][y].sq = ".`";
			}
		}
	}
	void get_drawed(Visitor* dv) override
	{
		dv->get_plate(this);
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
	void get_drawed(Visitor* dv) override
	{
		dv->get_plate(this);
	}
};
struct drawerVisitor :  public Visitor
{
	int end_of_scorePlate;
	char buffer[5000];
	void get_plate(ScorePlate* scorePlate) override
	{
		int count = 0;
		string sc = to_string(scorePlate->pointsLine);
		for (int i = 0; i < scorePlate->width - sc.size() / 2; i++)
		{
			buffer[count] = '-';
			count++;
		}
		for (int i = 0; i < sc.size(); i++)
		{
			buffer[count] = sc[i];
			count++;
		}
		while (count < scorePlate->width * 2)
		{
			buffer[count] = '-';
			count++;
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
	void get_plate(Fuild* fuild) override
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
		get_plate(scorePlate);
		get_plate(fuild);
		move_cursore_topleft();
		buffer[end_of_scorePlate] = '\0';
		puts(buffer);
	}
};