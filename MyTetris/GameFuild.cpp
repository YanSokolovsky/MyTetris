#pragma once
#include "settings.h"
#include <string>
#include "score.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <boost/thread.hpp>
#include "StartScene.h"
#include <boost/thread/mutex.hpp>
using namespace std;
boost::mutex mut, lrmut;
void clear_screen(char fill = ' ') {
	COORD topLeft = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, topLeft, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, topLeft, &written);
	SetConsoleCursorPosition(console, topLeft);
}
struct squer
{
	string sq;
	squer()
	{
		sq = "  ";
	}
	squer(string val)
	{
		sq = val;
	}
};
struct scorefuild
{
	string filename;
	int score;
	string animationLoader()
	{
		string line("");
		string resline("");
		string n = "\n";
		ifstream in(filename);
		int i = 0;
		if (in.is_open()) {
			while (getline(in, line)) {
				if (i != 0)
				{
					resline += n + line;
				}
				else
				{
					resline += line;
					i++;
				}
			}
		}
		in.close();
		return resline;
	};
	void drow(char* buff1)
	{
		char buff[1000];
		string load = animationLoader();
		strcpy_s(buff, load.c_str());
		for (int i = 0; i < load.length(); i++)
		{
			buff1[i] = buff[i];
		}
		buff1[load.length()] = '\n';
	}
};
struct fuild
{
	squer** f;
	bool gameover;
	int high;
	int wingth;
	char* buff;
	scorefuild* sf;
	fuild(int h, int w)
	{
		gameover = false;
		buff = new char[2 * h * w + h + 11 + 232];
		high = h;
		wingth = w;
		f = new squer * [h];
		for (int i = 0; i < h; i++)
		{
			f[i] = new squer[w];
			for (int b = 0; b < w; b++)
			{
				if (b == 0 || b == w - 1)
				{
					f[i][b] = squer("..");
					buff[i * 2 * w + i + 2 * b + 0] = '.';
					buff[i * 2 * w + i + 2 * b + 1] = '.';
					continue;
				}
				if (i == 0 && b < w - 1 && b > 0)
				{
					f[i][b] = squer("__");
					buff[i * 2 * w + i + 2 * b + 0] = '_';
					buff[i * 2 * w + i + 2 * b + 1] = '_';
					continue;
				}
				if (i == h - 1 && b < w - 1 && b > 0)
				{
					f[i][b] = squer("``");
					buff[i * 2 * w + i + 2 * b + 0] = '`';
					buff[i * 2 * w + i + 2 * b + 1] = '`';
					continue;
				}
				buff[i * 2 * w + i + 2 * b + 0] = ' ';
				buff[i * 2 * w + i + 2 * b + 1] = ' ';
				f[i][b] = squer();
			}
			buff[i * 2 * w + i + 2 * w] = '\n';
		}
		buff[h * 2 * w + h + 1] = '\0';
	}
	void show()
	{
		char buff1[5000];
		int count = 0;
		for (int i = 0; i < high; i++)
		{
			for (int y = 0; y < wingth; y++)
			{
				buff1[wingth * 11 + count] = f[i][y].sq[0];
				buff1[wingth * 11 + count + 1] = f[i][y].sq[1];
				count += 2;
			}
			buff1[wingth * 11 + count] = '\n';
			count++;
		}
		buff1[wingth * 11 + count] = '\0';
		COORD topLeft = { 0, 0 };
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(console, topLeft);
		sf->drow(buff1);
		puts(buff1);
	}
};
class brick
{
public:
	int ycenter;
	int xcenter;
	int position;
	bool exist;
	fuild* fld;
	virtual bool canrotate() { return true; };
	virtual bool canmoveright() { return true; };
	virtual bool canmoveleft() { return true; };
	virtual bool canmovedown() { return true; };
	virtual bool canbeputted() { return true; };
	virtual void movedown() { return; };
	virtual void moveleft() { return; };
	virtual void moveright() { return; };
	virtual void rotate() { return; };
	virtual void del() { return; };
	virtual void drow() { return; };
};
bool isfull(int i, fuild* fld)
{
	for (int y = 1; y < fld->wingth - 1; y++)
	{
		if (fld->f[i][y].sq != "[]")
		{
			return false;
		}
	}
	return true;
}
void deleter(int i, fuild* fld)
{
	for (int y = 1; y < fld->wingth - 1; y++)
	{
		fld->f[i][y].sq = "  ";
		fld->sf->score++;
	}
}
void moveall(int i, fuild* fld)
{
	for (int a = i - 1; a > 0; a--)
	{
		for (int b = 1; b < fld->wingth - 1; b++)
		{
			fld->f[a + 1][b].sq = fld->f[a][b].sq;
			fld->f[a][b].sq = "  ";
		}
	}
}
void worcker(fuild* fld)
{
	for (int i = 1; i < fld->high - 1; i++)
	{
		if (isfull(i, fld))
		{
			deleter(i, fld);
			moveall(i, fld);
		}
	}
}
struct Tbrick : public brick
{
	Tbrick(fuild* f)
	{
		ycenter = 3;
		xcenter = 7;
		position = 0;
		fld = f;
		exist = true;
		canbeputted();
	}
	bool canrotate() override
	{
		switch (position % 4)
		{
		case 0: if (fld->f[ycenter - 1][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2: if (fld->f[ycenter + 1][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 3:if (fld->f[ycenter][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveright()  override
	{
		switch (position % 4)
		{
		case 0: if (fld->f[ycenter][xcenter + 2].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter][xcenter + 2].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  " && fld->f[ycenter - 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2: if (fld->f[ycenter - 1][xcenter + 1].sq == "  " && fld->f[ycenter][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 3:if (fld->f[ycenter][xcenter + 1].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  " && fld->f[ycenter - 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveleft()  override
	{
		switch (position % 4)
		{
		case 0: if (fld->f[ycenter][xcenter - 2].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter][xcenter - 1].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  " && fld->f[ycenter - 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2: if (fld->f[ycenter - 1][xcenter - 1].sq == "  " && fld->f[ycenter][xcenter - 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 3:if (fld->f[ycenter][xcenter - 2].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  " && fld->f[ycenter - 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmovedown() override
	{
		switch (position % 4)
		{
		case 0: if (fld->f[ycenter + 2][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter + 1][xcenter + 1].sq == "  " && fld->f[ycenter + 2][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 2: if (fld->f[ycenter + 1][xcenter + 1].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  " && fld->f[ycenter + 1][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 3:if (fld->f[ycenter + 2][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canbeputted() override
	{
		if (fld->f[3][7].sq == "  " && fld->f[3][6].sq == "  " && fld->f[3][8].sq == "  " && fld->f[4][7].sq == "  ")
		{
			exist = true;
			return true;
		}
		else
		{
			exist = false;
			return false;
		}
	};
	void movedown() override
	{
		if (canmovedown())
		{
			del();
			ycenter++;
			drow();
		}
	};
	void moveleft() override
	{
		if (canmoveleft())
		{
			del();
			xcenter--;
			drow();
		}
	};
	void moveright() override
	{
		if (canmoveright())
		{
			del();
			xcenter++;
			drow();
		}
	};
	void rotate() override
	{
		if (canrotate())
		{
			del();
			position++;
			drow();
		}
	};
	void del() override
	{
		switch (position % 4)
		{
		case 0: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter + 1][xcenter].sq = "  "; fld->f[ycenter][xcenter - 1].sq = "  "; fld->f[ycenter][xcenter + 1].sq = "  "; break;
		case 1: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter + 1][xcenter].sq = "  "; fld->f[ycenter - 1][xcenter].sq = "  "; fld->f[ycenter][xcenter + 1].sq = "  "; break;
		case 2: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter - 1][xcenter].sq = "  "; fld->f[ycenter][xcenter - 1].sq = "  "; fld->f[ycenter][xcenter + 1].sq = "  "; break;
		case 3: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter + 1][xcenter].sq = "  "; fld->f[ycenter][xcenter - 1].sq = "  "; fld->f[ycenter - 1][xcenter].sq = "  "; break;
		}
	}
	void drow() override
	{
		switch (position % 4)
		{
		case 0: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter + 1][xcenter].sq = "[]"; fld->f[ycenter][xcenter - 1].sq = "[]"; fld->f[ycenter][xcenter + 1].sq = "[]"; break;
		case 1: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter + 1][xcenter].sq = "[]"; fld->f[ycenter - 1][xcenter].sq = "[]"; fld->f[ycenter][xcenter + 1].sq = "[]"; break;
		case 2: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter - 1][xcenter].sq = "[]"; fld->f[ycenter][xcenter - 1].sq = "[]"; fld->f[ycenter][xcenter + 1].sq = "[]"; break;
		case 3: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter + 1][xcenter].sq = "[]"; fld->f[ycenter][xcenter - 1].sq = "[]"; fld->f[ycenter - 1][xcenter].sq = "[]"; break;
		}
	};
};
struct Linebrick : public brick
{
	Linebrick(fuild* f)
	{
		ycenter = 3;
		xcenter = 7;
		position = 0;
		fld = f;
		exist = true;
		if (canbeputted())
		{
			exist = true;
		}
	}
	bool canrotate() override
	{
		switch (position % 2)
		{
		case 0: if (fld->f[ycenter - 1][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter + 2][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter][xcenter - 1].sq == "  " && fld->f[ycenter][xcenter + 1].sq == "  " && fld->f[ycenter][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveright() override
	{
		switch (position % 2)
		{
		case 0: if (fld->f[ycenter][xcenter + 3].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter - 1][xcenter + 1].sq == "  " && fld->f[ycenter][xcenter + 1].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  " && fld->f[ycenter + 2][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveleft() override
	{
		switch (position % 2)
		{
		case 0: if (fld->f[ycenter][xcenter - 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter - 1][xcenter - 1].sq == "  " && fld->f[ycenter][xcenter - 1].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  " && fld->f[ycenter + 2][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmovedown() override
	{
		switch (position % 2)
		{
		case 0: if (fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  " && fld->f[ycenter + 1][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter + 3][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canbeputted() override
	{
		if (fld->f[ycenter][xcenter - 1].sq == "  " && fld->f[ycenter][xcenter].sq == "  " && fld->f[ycenter][xcenter + 1].sq == "  " && fld->f[ycenter][xcenter + 2].sq == "  ") { exist = true; return true; }
		else { fld->gameover = true; exist = false; return false; }
	};
	void movedown() override
	{
		if (canmovedown())
		{
			del();
			ycenter++;
			drow();
		}
	};
	void moveleft() override
	{
		if (canmoveleft())
		{
			del();
			xcenter--;
			drow();
		}
	};
	void moveright() override
	{
		if (canmoveright())
		{
			del();
			xcenter++;
			drow();
		}
	};
	void rotate() override
	{
		if (canrotate())
		{
			del();
			position++;
			drow();
		}
	};
	void del() override
	{
		switch (position % 2)
		{
		case 0: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter][xcenter - 1].sq = "  "; fld->f[ycenter][xcenter + 1].sq = "  "; fld->f[ycenter][xcenter + 2].sq = "  "; break;
		case 1: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter - 1][xcenter].sq = "  "; fld->f[ycenter + 1][xcenter].sq = "  "; fld->f[ycenter + 2][xcenter].sq = "  "; break;
		}
	};
	void drow() override
	{
		switch (position % 2)
		{
		case 0: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter][xcenter - 1].sq = "[]"; fld->f[ycenter][xcenter + 1].sq = "[]"; fld->f[ycenter][xcenter + 2].sq = "[]"; break;
		case 1: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter - 1][xcenter].sq = "[]"; fld->f[ycenter + 1][xcenter].sq = "[]"; fld->f[ycenter + 2][xcenter].sq = "[]"; break;
		}
	};
};
struct Lbrick : public brick
{
	Lbrick(fuild* f)
	{
		ycenter = 3;
		xcenter = 7;
		position = 0;
		fld = f;
		exist = true;
		if (canbeputted())
		{
			exist = true;
		}
	}
	bool canrotate() override
	{
		switch (position % 4)
		{
		case 0: if (fld->f[ycenter - 1][xcenter].sq == "  " && fld->f[ycenter - 2][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter][xcenter - 1].sq == "  " && fld->f[ycenter][xcenter - 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter + 2][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fld->f[ycenter][xcenter + 1].sq == "  " && fld->f[ycenter][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveright() override
	{
		switch (position % 4)
		{
		case 0: if (fld->f[ycenter][xcenter + 3].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter][xcenter + 2].sq == "  " && fld->f[ycenter - 1][xcenter + 1].sq == "  " && fld->f[ycenter - 2][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fld->f[ycenter][xcenter + 1].sq == "  " && fld->f[ycenter - 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fld->f[ycenter][xcenter + 1].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  " && fld->f[ycenter + 2][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveleft() override
	{
		switch (position % 4)
		{
		case 0: if (fld->f[ycenter][xcenter - 1].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter][xcenter - 1].sq == "  " && fld->f[ycenter - 1][xcenter - 1].sq == "  " && fld->f[ycenter - 2][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fld->f[ycenter][xcenter - 3].sq == "  " && fld->f[ycenter - 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fld->f[ycenter][xcenter - 2].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  " && fld->f[ycenter + 2][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmovedown() override
	{
		switch (position % 4)
		{
		case 0: if (fld->f[ycenter + 2][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  " && fld->f[ycenter + 1][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  " && fld->f[ycenter + 1][xcenter - 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fld->f[ycenter + 1][xcenter - 1].sq == "  " && fld->f[ycenter + 3][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canbeputted() override
	{
		if (fld->f[ycenter][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter][xcenter + 1].sq == "  " && fld->f[ycenter][xcenter + 2].sq == "  ")
		{
			exist = true;
			return true;
		}
		else
		{
			fld->gameover = true;
			exist = false;
			return true;
		}
	};
	void movedown() override
	{
		if (canmovedown())
		{
			del();
			ycenter++;
			drow();
		}
	};
	void moveleft() override
	{
		if (canmoveleft())
		{
			del();
			xcenter--;
			drow();
		}
	};
	void moveright() override
	{
		if (canmoveright())
		{
			del();
			xcenter++;
			drow();
		}
	};
	void rotate() override
	{
		if (canrotate())
		{
			del();
			position++;
			drow();
		}
	};
	void del() override
	{
		switch (position % 4)
		{
		case 0: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter + 1][xcenter].sq = "  "; fld->f[ycenter][xcenter + 2].sq = "  "; fld->f[ycenter][xcenter + 1].sq = "  "; break;
		case 1: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter][xcenter + 1].sq = "  "; fld->f[ycenter - 1][xcenter].sq = "  "; fld->f[ycenter - 2][xcenter].sq = "  "; break;
		case 2: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter - 1][xcenter].sq = "  "; fld->f[ycenter][xcenter - 1].sq = "  "; fld->f[ycenter][xcenter - 2].sq = "  "; break;
		case 3: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter][xcenter - 1].sq = "  "; fld->f[ycenter + 1][xcenter].sq = "  "; fld->f[ycenter + 2][xcenter].sq = "  "; break;
		}
	};
	void drow() override
	{
		switch (position % 4)
		{
		case 0: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter + 1][xcenter].sq = "[]"; fld->f[ycenter][xcenter + 2].sq = "[]"; fld->f[ycenter][xcenter + 1].sq = "[]"; break;
		case 1: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter][xcenter + 1].sq = "[]"; fld->f[ycenter - 1][xcenter].sq = "[]"; fld->f[ycenter - 2][xcenter].sq = "[]"; break;
		case 2: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter - 1][xcenter].sq = "[]"; fld->f[ycenter][xcenter - 1].sq = "[]"; fld->f[ycenter][xcenter - 2].sq = "[]"; break;
		case 3: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter][xcenter - 1].sq = "[]"; fld->f[ycenter + 1][xcenter].sq = "[]"; fld->f[ycenter + 2][xcenter].sq = "[]"; break;
		}
	};
};
struct RLbrick : public brick
{
	RLbrick(fuild* f)
	{
		ycenter = 3;
		xcenter = 7;
		position = 0;
		fld = f;
		exist = true;
		if (canbeputted())
		{
			exist = true;
		}
	}
	bool canrotate() override
	{
		switch (position % 4)
		{
		case 0: if (fld->f[ycenter][xcenter - 1].sq == "  " && fld->f[ycenter - 2][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter][xcenter - 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fld->f[ycenter][xcenter + 1].sq == "  " && fld->f[ycenter + 2][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fld->f[ycenter - 1][xcenter].sq == "  " && fld->f[ycenter][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveright() override
	{
		switch (position % 4)
		{
		case 0: if (fld->f[ycenter - 1][xcenter + 1].sq == "  " && fld->f[ycenter][xcenter + 3].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter][xcenter + 1].sq == "  " && fld->f[ycenter - 1][xcenter + 1].sq == "  " && fld->f[ycenter - 2][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fld->f[ycenter][xcenter + 1].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fld->f[ycenter][xcenter + 2].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  " && fld->f[ycenter + 2][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveleft() override
	{
		switch (position % 4)
		{
		case 0: if (fld->f[ycenter][xcenter - 1].sq == "  " && fld->f[ycenter - 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter][xcenter - 2].sq == "  " && fld->f[ycenter - 1][xcenter - 1].sq == "  " && fld->f[ycenter - 2][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fld->f[ycenter][xcenter - 3].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fld->f[ycenter][xcenter - 1].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  " && fld->f[ycenter + 2][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmovedown() override
	{
		switch (position % 4)
		{
		case 0: if (fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  " && fld->f[ycenter + 1][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 2:if (fld->f[ycenter + 2][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  " && fld->f[ycenter + 1][xcenter - 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 3: if (fld->f[ycenter + 1][xcenter + 1].sq == "  " && fld->f[ycenter + 3][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canbeputted() override
	{
		if (fld->f[ycenter][xcenter].sq == "  " && fld->f[ycenter - 1][xcenter].sq == "  " && fld->f[ycenter][xcenter + 2].sq == "  " && fld->f[ycenter][xcenter + 1].sq == "  ") { exist = true; return true; }
		else { fld->gameover = true; exist = false; return false; }
	};
	void movedown() override
	{
		if (canmovedown())
		{
			del();
			ycenter++;
			drow();
		}
	};
	void moveleft() override
	{
		if (canmoveleft())
		{
			del();
			xcenter--;
			drow();
		}
	};
	void moveright() override
	{
		if (canmoveright())
		{
			del();
			xcenter++;
			drow();
		}
	};
	void rotate() override
	{
		if (canrotate())
		{
			del();
			position++;
			drow();
		}
	};
	void del() override
	{
		switch (position % 4)
		{
		case 0: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter - 1][xcenter].sq = "  "; fld->f[ycenter][xcenter + 2].sq = "  "; fld->f[ycenter][xcenter + 1].sq = "  "; break;
		case 1: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter][xcenter - 1].sq = "  "; fld->f[ycenter - 1][xcenter].sq = "  "; fld->f[ycenter - 2][xcenter].sq = "  "; break;
		case 2: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter + 1][xcenter].sq = "  "; fld->f[ycenter][xcenter - 1].sq = "  "; fld->f[ycenter][xcenter - 2].sq = "  "; break;
		case 3: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter][xcenter + 1].sq = "  "; fld->f[ycenter + 1][xcenter].sq = "  "; fld->f[ycenter + 2][xcenter].sq = "  "; break;
		}
	};
	void drow() override
	{
		switch (position % 4)
		{
		case 0: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter - 1][xcenter].sq = "[]"; fld->f[ycenter][xcenter + 2].sq = "[]"; fld->f[ycenter][xcenter + 1].sq = "[]"; break;
		case 1: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter][xcenter - 1].sq = "[]"; fld->f[ycenter - 1][xcenter].sq = "[]"; fld->f[ycenter - 2][xcenter].sq = "[]"; break;
		case 2: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter + 1][xcenter].sq = "[]"; fld->f[ycenter][xcenter - 1].sq = "[]"; fld->f[ycenter][xcenter - 2].sq = "[]"; break;
		case 3: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter][xcenter + 1].sq = "[]"; fld->f[ycenter + 1][xcenter].sq = "[]"; fld->f[ycenter + 2][xcenter].sq = "[]"; break;
		}
	};
};
struct Zbrick : public brick
{
	Zbrick(fuild* f)
	{
		ycenter = 3;
		xcenter = 7;
		position = 0;
		fld = f;
		exist = true;
		if (canbeputted())
		{
			exist = true;
		}
	}
	bool canrotate() override
	{
		switch (position % 2)
		{
		case 0: if (fld->f[ycenter - 1][xcenter].sq == "  " && fld->f[ycenter - 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveright() override
	{
		switch (position % 2)
		{
		case 0: if (fld->f[ycenter][xcenter + 1].sq == "  " && fld->f[ycenter + 1][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter][xcenter + 1].sq == "  " && fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter - 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveleft() override
	{
		switch (position % 2)
		{
		case 0: if (fld->f[ycenter][xcenter - 2].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter][xcenter - 2].sq == "  " && fld->f[ycenter - 1][xcenter - 1].sq == "  " && fld->f[ycenter + 1][xcenter - 2].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmovedown() override
	{
		switch (position % 2)
		{
		case 0: if (fld->f[ycenter + 1][xcenter - 1].sq == "  " && fld->f[ycenter + 2][xcenter].sq == "  " && fld->f[ycenter + 2][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter + 2][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canbeputted() override
	{
		if (fld->f[ycenter][xcenter].sq == "  " && fld->f[ycenter][xcenter - 1].sq == "  " && fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  ")
		{
			exist = true;
			return true;
		}
		else
		{
			fld->gameover = true;
			exist = false;
			return false;
		}
	};
	void movedown() override
	{
		if (canmovedown())
		{
			del();
			ycenter++;
			drow();
		}
	};
	void moveleft() override
	{
		if (canmoveleft())
		{
			del();
			xcenter--;
			drow();
		}
	};
	void moveright() override
	{
		if (canmoveright())
		{
			del();
			xcenter++;
			drow();
		}
	};
	void rotate() override
	{
		if (canrotate())
		{
			del();
			position++;
			drow();
		}
	};
	void del() override
	{
		switch (position % 2)
		{
		case 0: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter][xcenter - 1].sq = "  "; fld->f[ycenter + 1][xcenter].sq = "  "; fld->f[ycenter + 1][xcenter + 1].sq = "  "; break;
		case 1: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter - 1][xcenter].sq = "  "; fld->f[ycenter][xcenter - 1].sq = "  "; fld->f[ycenter + 1][xcenter - 1].sq = "  "; break;
		}
	};
	void drow() override
	{
		switch (position % 2)
		{
		case 0: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter][xcenter - 1].sq = "[]"; fld->f[ycenter + 1][xcenter].sq = "[]"; fld->f[ycenter + 1][xcenter + 1].sq = "[]"; break;
		case 1: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter - 1][xcenter].sq = "[]"; fld->f[ycenter][xcenter - 1].sq = "[]"; fld->f[ycenter + 1][xcenter - 1].sq = "[]"; break;
		}
	};
};
struct RZbrick : public brick
{
	RZbrick(fuild* f)
	{
		ycenter = 3;
		xcenter = 7;
		position = 0;
		fld = f;
		exist = true;
		if (canbeputted())
		{
			exist = true;
		}
	}
	bool canrotate() override
	{
		switch (position % 2)
		{
		case 0: if (fld->f[ycenter - 1][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveright() override
	{
		switch (position % 2)
		{
		case 0: if (fld->f[ycenter + 1][xcenter + 1].sq == "  " && fld->f[ycenter][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter - 1][xcenter + 1].sq == "  " && fld->f[ycenter][xcenter + 2].sq == "  " && fld->f[ycenter + 1][xcenter + 2].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmoveleft() override
	{
		switch (position % 2)
		{
		case 0: if (fld->f[ycenter + 1][xcenter - 2].sq == "  " && fld->f[ycenter][xcenter - 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter][xcenter - 1].sq == "  " && fld->f[ycenter - 1][xcenter - 1].sq == "  " && fld->f[ycenter + 1][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canmovedown() override
	{
		switch (position % 2)
		{
		case 0: if (fld->f[ycenter + 2][xcenter].sq == "  " && fld->f[ycenter + 2][xcenter - 1].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  ") { return true; }
			  else { return false; } break;
		case 1: if (fld->f[ycenter + 2][xcenter + 1].sq == "  " && fld->f[ycenter + 1][xcenter].sq == "  ") { return true; }
			  else { return false; } break;
		}
	};
	bool canbeputted() override
	{
		if (fld->f[ycenter][xcenter].sq == "  " && fld->f[ycenter][xcenter + 1].sq == "  " && fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  ")
		{
			exist = true;
			return true;
		}
		else
		{
			fld->gameover = true;
			exist = false;
			return false;
		}
	};
	void movedown() override
	{
		if (canmovedown())
		{
			del();
			ycenter++;
			drow();
		}
	};
	void moveleft() override
	{
		if (canmoveleft())
		{
			del();
			xcenter--;
			drow();
		}
	};
	void moveright() override
	{
		if (canmoveright())
		{
			del();
			xcenter++;
			drow();
		}
	};
	void rotate() override
	{
		if (canrotate())
		{
			del();
			position++;
			drow();
		}
	};
	void del() override
	{
		switch (position % 2)
		{
		case 0: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter][xcenter + 1].sq = "  "; fld->f[ycenter + 1][xcenter].sq = "  "; fld->f[ycenter + 1][xcenter - 1].sq = "  "; break;
		case 1: fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter - 1][xcenter].sq = "  "; fld->f[ycenter][xcenter + 1].sq = "  "; fld->f[ycenter + 1][xcenter + 1].sq = "  "; break;
		}
	};
	void drow() override
	{
		switch (position % 2)
		{
		case 0: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter][xcenter + 1].sq = "[]"; fld->f[ycenter + 1][xcenter].sq = "[]"; fld->f[ycenter + 1][xcenter - 1].sq = "[]"; break;
		case 1: fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter - 1][xcenter].sq = "[]"; fld->f[ycenter][xcenter + 1].sq = "[]"; fld->f[ycenter + 1][xcenter + 1].sq = "[]"; break;
		}
	};
};
struct SQbrick : public brick
{
	SQbrick(fuild* f)
	{
		ycenter = 3;
		xcenter = 7;
		position = 0;
		fld = f;
		exist = true;
		if (canbeputted())
		{
			exist = true;
		}
	}
	bool canrotate() override
	{
		return true;
	};
	bool canmoveright() override
	{
		if (fld->f[ycenter][xcenter + 2].sq == "  " && fld->f[ycenter + 1][xcenter + 2].sq == "  ") { return true; }
		else { return false; }
	};
	bool canmoveleft() override
	{
		if (fld->f[ycenter][xcenter - 1].sq == "  " && fld->f[ycenter + 1][xcenter - 1].sq == "  ") { return true; }
		else { return false; }
	};
	bool canmovedown() override
	{
		if (fld->f[ycenter + 2][xcenter].sq == "  " && fld->f[ycenter + 2][xcenter + 1].sq == "  ") { return true; }
		else { return false; }
	};
	bool canbeputted() override
	{
		if (fld->f[ycenter][xcenter].sq == "  " && fld->f[ycenter][xcenter + 1].sq == "  " && fld->f[ycenter + 1][xcenter].sq == "  " && fld->f[ycenter + 1][xcenter + 1].sq == "  ")
		{
			exist = true;
			return true;
		}
		else
		{
			fld->gameover = true;
			exist = false;
			return false;
		}
	};
	void movedown() override
	{
		if (canmovedown())
		{
			del();
			ycenter++;
			drow();
		}
	};
	void moveleft() override
	{
		if (canmoveleft())
		{
			del();
			xcenter--;
			drow();
		}
	};
	void moveright() override
	{
		if (canmoveright())
		{
			del();
			xcenter++;
			drow();
		}
	};
	void rotate() override
	{
		if (canrotate())
		{
			del();
			position++;
			drow();
		}
	};
	void del() override
	{
		fld->f[ycenter][xcenter].sq = "  "; fld->f[ycenter][xcenter + 1].sq = "  "; fld->f[ycenter + 1][xcenter].sq = "  "; fld->f[ycenter + 1][xcenter + 1].sq = "  ";
	};
	void drow() override
	{
		fld->f[ycenter][xcenter].sq = "[]"; fld->f[ycenter][xcenter + 1].sq = "[]"; fld->f[ycenter + 1][xcenter].sq = "[]"; fld->f[ycenter + 1][xcenter + 1].sq = "[]";
	};
};
void drop(brick* t, settings* setin)
{
	int i = 1000;
	while (true)
	{
		if (t->exist)
		{
			mut.lock();
			t->movedown();
			t->fld->show();
			mut.unlock();
		}
		else
		{
			return;
		}
		Sleep(i / setin->speed);
	}
}
void rot(brick* t, settings* setin, fuild* fld)
{
	while (t->exist)
	{
		if (GetAsyncKeyState(VK_UP)) {
			mut.lock();
			t->rotate();
			fld->show();
			mut.unlock();
			if (GetAsyncKeyState(VK_UP) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_UP) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_UP) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_UP) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_UP) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_UP) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_UP) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_UP) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_UP) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_UP) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_UP) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_UP) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_UP) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_UP) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_UP) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			while (GetAsyncKeyState(VK_UP) && t->exist)
			{
				mut.lock();
				t->rotate();
				fld->show();
				mut.unlock();
				Sleep(90);
			}
		}
	}
}
void down(brick* t, settings* setin, fuild* fld)
{
	while (t->exist)
	{
		if (GetAsyncKeyState(VK_DOWN)) {
			mut.lock();
			t->movedown();
			fld->show();
			mut.unlock();
			Sleep(100);
		}
	}
}
void le(brick* t, settings* setin, fuild* fld)
{
	while (t->exist)
	{
		if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist) {
			mut.lock();
			t->moveleft();
			fld->show();
			mut.unlock();
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			while (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				mut.lock();
				t->moveleft();
				fld->show();
				mut.unlock();
				Sleep(90);
			}
		}
	}
}
void ri(brick* t, settings* setin, fuild* fld)
{
	while (t->exist)
	{
		if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT)) {
			mut.lock();
			t->moveright();
			fld->show();
			mut.unlock();
			if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				Sleep(10);
			}
			else
			{
				continue;
			}
			while (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				mut.lock();
				t->moveright();
				fld->show();
				mut.unlock();
				Sleep(90);
			}
		}
	}
}
void Tgame(settings* setin, fuild* fld)
{
	Tbrick* t = new Tbrick(fld);
	int i = 0;
	boost::thread th(drop, (brick*)t, setin);
	boost::thread th1(rot, (brick*)t, setin, fld);
	boost::thread th2(down, (brick*)t, setin, fld);
	boost::thread th3(le, (brick*)t, setin, fld);
	boost::thread th4(ri, (brick*)t, setin, fld);
	while (true) {
		if (!t->canmovedown())
		{
			i++;
		}
		else
		{
			i = 0;
		}
		if (i == 2)
		{
			t->exist = false;
			return;
		}
		else
		{
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			t->exist = false;
			fld->gameover = true;
			system("mode con cols=63 lines=34");
			clear_screen();
			return;
		}
	}
}
void Linegame(settings* setin, fuild* fld)
{
	Linebrick* t = new Linebrick(fld);
	int i = 0;
	boost::thread th(drop, (brick*)t, setin);
	boost::thread th1(rot, (brick*)t, setin, fld);
	boost::thread th2(down, (brick*)t, setin, fld);
	boost::thread th3(le, (brick*)t, setin, fld);
	boost::thread th4(ri, (brick*)t, setin, fld);
	while (true) {
		if (!t->canmovedown())
		{
			i++;
		}
		else
		{
			i = 0;
		}
		if (i == 2)
		{
			t->exist = false;
			return;
		}
		else
		{
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			t->exist = false;
			fld->gameover = true;
			system("mode con cols=63 lines=34");
			clear_screen();
			return;
		}
	}
}
void Lgame(settings* setin, fuild* fld)
{
	Lbrick* t = new Lbrick(fld);
	int i = 0;
	boost::thread th(drop, (brick*)t, setin);
	boost::thread th1(rot, (brick*)t, setin, fld);
	boost::thread th2(down, (brick*)t, setin, fld);
	boost::thread th3(le, (brick*)t, setin, fld);
	boost::thread th4(ri, (brick*)t, setin, fld);
	while (true) {
		if (!t->canmovedown())
		{
			i++;
		}
		else
		{
			i = 0;
		}
		if (i == 2)
		{
			t->exist = false;
			return;
		}
		else
		{
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			t->exist = false;
			fld->gameover = true;
			system("mode con cols=63 lines=34");
			clear_screen();
			return;
		}
	}
}
void RLgame(settings* setin, fuild* fld)
{
	RLbrick* t = new RLbrick(fld);
	int i = 0;
	boost::thread th(drop, (brick*)t, setin);
	boost::thread th1(rot, (brick*)t, setin, fld);
	boost::thread th2(down, (brick*)t, setin, fld);
	boost::thread th3(le, (brick*)t, setin, fld);
	boost::thread th4(ri, (brick*)t, setin, fld);
	while (true) {
		if (!t->canmovedown())
		{
			i++;
		}
		else
		{
			i = 0;
		}
		if (i == 2)
		{
			t->exist = false;
			return;
		}
		else
		{
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			t->exist = false;
			fld->gameover = true;
			system("mode con cols=63 lines=34");
			clear_screen();
			return;
		}
	}
}
void Zgame(settings* setin, fuild* fld)
{
	Zbrick* t = new Zbrick(fld);
	int i = 0;
	boost::thread th(drop, (brick*)t, setin);
	boost::thread th1(rot, (brick*)t, setin, fld);
	boost::thread th2(down, (brick*)t, setin, fld);
	boost::thread th3(le, (brick*)t, setin, fld);
	boost::thread th4(ri, (brick*)t, setin, fld);
	while (true) {
		if (!t->canmovedown())
		{
			i++;
		}
		else
		{
			i = 0;
		}
		if (i == 2)
		{
			t->exist = false;
			return;
		}
		else
		{
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			t->exist = false;
			fld->gameover = true;
			system("mode con cols=63 lines=34");
			clear_screen();
			return;
		}
	}
}
void RZgame(settings* setin, fuild* fld)
{
	RZbrick* t = new RZbrick(fld);
	int i = 0;
	boost::thread th(drop, (brick*)t, setin);
	boost::thread th1(rot, (brick*)t, setin, fld);
	boost::thread th2(down, (brick*)t, setin, fld);
	boost::thread th3(le, (brick*)t, setin, fld);
	boost::thread th4(ri, (brick*)t, setin, fld);
	while (true) {
		if (!t->canmovedown())
		{
			i++;
		}
		else
		{
			i = 0;
		}
		if (i == 2)
		{
			t->exist = false;
			return;
		}
		else
		{
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			t->exist = false;
			fld->gameover = true;
			system("mode con cols=63 lines=34");
			clear_screen();
			return;
		}
	}
}
void SQgame(settings* setin, fuild* fld)
{
	SQbrick* t = new SQbrick(fld);
	int i = 0;
	boost::thread th(drop, (brick*)t, setin);
	boost::thread th1(rot, (brick*)t, setin, fld);
	boost::thread th2(down, (brick*)t, setin, fld);
	boost::thread th3(le, (brick*)t, setin, fld);
	boost::thread th4(ri, (brick*)t, setin, fld);
	while (true) {
		if (!t->canmovedown())
		{
			i++;
		}
		else
		{
			i = 0;
		}
		if (i == 2)
		{
			t->exist = false;
			return;
		}
		else
		{
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			t->exist = false;
			fld->gameover = true;
			system("mode con cols=63 lines=34");
			clear_screen();
			return;
		}
	}
}
void choosenext(int i, scorefuild* sr)
{
	switch (i)
	{
	case 0:sr->filename = "tscorepanel.txt"; break;
	case 1:sr->filename = "linescorepanel.txt"; break;
	case 2:sr->filename = "lscorepanel.txt"; break;
	case 3:sr->filename = "rlscorepanel.txt"; break;
	case 4:sr->filename = "zscorepanel.txt"; break;
	case 5:sr->filename = "rzsrocepanel.txt"; break;
	case 6:sr->filename = "sqscorepanel.txt"; break;
	}
}
void startgame(settings* setin, score* scr)
{
	string s1 = "mode con cols=";
	string par1 = to_string((setin->windth + 2) * 2);
	string s2 = " lines=";
	string par2 = to_string(setin->high + 12);
	system((s1 + par1 + s2 + par2).c_str());
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(console, &info);
	scorefuild* score = new scorefuild();
	fuild* fld = new fuild(setin->high + 2, setin->windth + 2);
	fld->sf = score;
	score->filename = "rlscorepanel.txt";
	fld->show();
	srand(time(NULL));
	int i = rand() % 7;
	choosenext(i, score);
	while (true) {
		if (i == 0)
		{
			boost::thread g(Tgame, setin, fld);
			srand(time(NULL));
			i = rand() % 7;
			choosenext(i, score);
			g.join();
		}
		if (fld->gameover)
		{
			clear_screen();
			system("mode con cols=63 lines=34");
			cout << animationLoader("gameover1.txt");
			Sleep(3000);
			break;
		}
		worcker(fld);
		if (i == 1)
		{
			boost::thread g(Linegame, setin, fld);
			srand(time(NULL));
			i = rand() % 7;
			choosenext(i, score);
			g.join();
		}
		if (fld->gameover)
		{
			clear_screen();
			system("mode con cols=63 lines=34");
			cout << animationLoader("gameover1.txt");
			Sleep(3000);
			break;
		}
		worcker(fld);
		if (i == 2)
		{
			boost::thread g(Lgame, setin, fld);
			srand(time(NULL));
			i = rand() % 7;
			choosenext(i, score);
			g.join();
		}
		if (fld->gameover)
		{
			clear_screen();
			system("mode con cols=63 lines=34");
			cout << animationLoader("gameover1.txt");
			Sleep(3000);
			break;
		}
		worcker(fld);
		if (i == 3)
		{
			boost::thread g(RLgame, setin, fld);
			srand(time(NULL));
			i = rand() % 7;
			choosenext(i, score);
			g.join();
		}
		if (fld->gameover)
		{
			clear_screen();
			system("mode con cols=63 lines=34");
			cout << animationLoader("gameover1.txt");
			Sleep(3000);
			break;
		}
		worcker(fld);
		if (i == 4)
		{
			boost::thread g(Zgame, setin, fld);
			srand(time(NULL));
			i = rand() % 7;
			choosenext(i, score);
			g.join();
		}
		if (fld->gameover)
		{
			clear_screen();
			system("mode con cols=63 lines=34");
			cout << animationLoader("gameover1.txt");
			Sleep(3000);
			break;
		}
		worcker(fld);
		if (i == 5)
		{
			boost::thread g(RZgame, setin, fld);
			srand(time(NULL));
			i = rand() % 7;
			choosenext(i, score);
			g.join();
		}
		if (fld->gameover)
		{
			clear_screen();
			system("mode con cols=63 lines=34");
			cout << animationLoader("gameover1.txt");
			Sleep(3000);
			break;
		}
		worcker(fld);
		if (i == 6)
		{
			boost::thread g(SQgame, setin, fld);
			srand(time(NULL));
			i = rand() % 7;
			choosenext(i, score);
			g.join();
		}
		if (fld->gameover)
		{
			clear_screen();
			system("mode con cols=63 lines=34");
			cout << animationLoader("gameover1.txt");
			Sleep(3000);
			break;
		}
		worcker(fld);
	}
	system("mode con cols=63 lines=34");
};