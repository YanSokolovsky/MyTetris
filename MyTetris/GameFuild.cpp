#pragma once
#include "Settings.h"
#include "Score.h"
#include "Plates.h"
#include "Bricks.h"
#include "Squer.h"

#include <string>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <boost/thread.hpp>
#include "StartScene.h"
#include <boost/thread/mutex.hpp>
using namespace std;
boost::mutex mut, lrmut;

bool isfull(int i, Plate* fuild)
{
	for (int y = 1; y < fuild->width - 1; y++)
	{
		if (fuild->f[i][y].sq != "[]")
		{
			return false;
		}
	}
	return true;
}
void deleter(int i, Plate* fuild)
{
	for (int y = 1; y < fuild->width - 1; y++)
	{
		fuild->f[i][y].sq = "  ";
	}
}
void moveall(int i, Plate* fuild)
{
	for (int a = i - 1; a > 0; a--)
	{
		for (int b = 1; b < fuild->width - 1; b++)
		{
			fuild->f[a + 1][b].sq = fuild->f[a][b].sq;
			fuild->f[a][b].sq = "  ";
		}
	}
}
void worcker(Plate* fuild)
{
	for (int i = 1; i < fuild->height - 1; i++)
	{
		if (isfull(i, fuild))
		{
			deleter(i, fuild);
			moveall(i, fuild);
		}
	}
}
void drop(brick* t, Settings* settings)
{
	int i = 1000;
	while (true)
	{
		if (t->exist)
		{
			mut.lock();
			t->movedown();

			mut.unlock();
		}
		else
		{
			return;
		}
		Sleep(i / settings->speed);
	}
}
void rot(brick* t, Settings* settings, Plate* fuild)
{
	while (t->exist)
	{
		if (GetAsyncKeyState(VK_UP)) {
			mut.lock();
			t->rotate();

			mut.unlock();
			for (int i = 0; i < 15 && GetAsyncKeyState(VK_UP) & 0x8000; i++)
			{
				Sleep(10);
			}
			while (GetAsyncKeyState(VK_UP) && t->exist)
			{
				mut.lock();
				t->rotate();

				mut.unlock();
				Sleep(90);
			}
		}
	}
}
void down(brick* t, Settings* settings, Plate* fuild)
{
	while (t->exist)
	{
		if (GetAsyncKeyState(VK_DOWN)) {
			mut.lock();
			t->movedown();
			// тут рисовать надо 
			mut.unlock();
			Sleep(100);
		}
	}
}
void le(brick* t, Settings* settings, Plate* fuild)
{
	while (t->exist)
	{
		if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist) {
			mut.lock();
			t->moveleft();

			mut.unlock();
			for (int i = 0; i < 15 && GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT); i++)
			{
				Sleep(10);
			}
			while (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				mut.lock();
				t->moveleft();

				mut.unlock();
				Sleep(90);
			}
		}
	}
}
void ri(brick* t, Settings* settings, Plate* fuild)
{
	while (t->exist)
	{
		if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT)) {
			mut.lock();
			t->moveright();
             // тут тозе
			mut.unlock();
			for (int i = 0; i < 15 && !GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT); i++)
			{
				Sleep(10);
			}
			while (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				mut.lock();
				t->moveright();

				mut.unlock();
				Sleep(90);
			}
		}
	}
}
void Tgame(Settings* settings, Plate* fuild)
{
	Tbrick* t = new Tbrick(fuild, settings->width / 2, 3);
	int i = 0;
	boost::thread th(drop, (brick*)t, settings);
	boost::thread th1(rot, (brick*)t, settings, fuild);
	boost::thread th2(down, (brick*)t, settings, fuild);
	boost::thread th3(le, (brick*)t, settings, fuild);
	boost::thread th4(ri, (brick*)t, settings, fuild);
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
			fuild->gameover = true;
			system("mode con cols=63 lines=34");
			return;
		}
	}
}
void Linegame(Settings* settings, Plate* fuild)
{
	Linebrick* t = new Linebrick(fuild, settings->width / 2, 3);
	int i = 0;
	boost::thread th(drop, (brick*)t, settings);
	boost::thread th1(rot, (brick*)t, settings, fuild);
	boost::thread th2(down, (brick*)t, settings, fuild);
	boost::thread th3(le, (brick*)t, settings, fuild);
	boost::thread th4(ri, (brick*)t, settings, fuild);
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
			fuild->gameover = true;
			system("mode con cols=63 lines=34");

			return;
		}
	}
}
void Lgame(Settings* settings, Plate* fuild)
{
	Lbrick* t = new Lbrick(fuild, settings->width / 2, 3);
	int i = 0;
	boost::thread th(drop, (brick*)t, settings);
	boost::thread th1(rot, (brick*)t, settings, fuild);
	boost::thread th2(down, (brick*)t, settings, fuild);
	boost::thread th3(le, (brick*)t, settings, fuild);
	boost::thread th4(ri, (brick*)t, settings, fuild);
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
			fuild->gameover = true;
			system("mode con cols=63 lines=34");

			return;
		}
	}
}
void RLgame(Settings* settings, Plate* fuild)
{
	RLbrick* t = new RLbrick(fuild, settings->width / 2, 3);
	int i = 0;
	boost::thread th(drop, (brick*)t, settings);
	boost::thread th1(rot, (brick*)t, settings, fuild);
	boost::thread th2(down, (brick*)t, settings, fuild);
	boost::thread th3(le, (brick*)t, settings, fuild);
	boost::thread th4(ri, (brick*)t, settings, fuild);
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
			fuild->gameover = true;
			system("mode con cols=63 lines=34");

			return;
		}
	}
}
void Zgame(Settings* settings, Plate* fuild)
{
	Zbrick* t = new Zbrick(fuild, settings->width / 2, 3);
	int i = 0;
	boost::thread th(drop, (brick*)t, settings);
	boost::thread th1(rot, (brick*)t, settings, fuild);
	boost::thread th2(down, (brick*)t, settings, fuild);
	boost::thread th3(le, (brick*)t, settings, fuild);
	boost::thread th4(ri, (brick*)t, settings, fuild);
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
			fuild->gameover = true;
			system("mode con cols=63 lines=34");

			return;
		}
	}
}
void RZgame(Settings* settings, Plate* fuild)
{
	RZbrick* t = new RZbrick(fuild, settings->width / 2, 3);
	int i = 0;
	boost::thread th(drop, (brick*)t, settings);
	boost::thread th1(rot, (brick*)t, settings, fuild);
	boost::thread th2(down, (brick*)t, settings, fuild);
	boost::thread th3(le, (brick*)t, settings, fuild);
	boost::thread th4(ri, (brick*)t, settings, fuild);
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
			fuild->gameover = true;
			system("mode con cols=63 lines=34");

			return;
		}
	}
}
void SQgame(Settings* settings, Plate* fuild)
{
	SQbrick* t = new SQbrick(fuild, settings->width / 2, 3);
	int i = 0;
	boost::thread th(drop, (brick*)t, settings);
	boost::thread th1(rot, (brick*)t, settings, fuild);
	boost::thread th2(down, (brick*)t, settings, fuild);
	boost::thread th3(le, (brick*)t, settings, fuild);
	boost::thread th4(ri, (brick*)t, settings, fuild);
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
			fuild->gameover = true;
			system("mode con cols=63 lines=34");

			return;
		}
	}
}
void game_launch(Settings* settings, Score* score)
{
	set_console_size_by_chars(settings->height + 6, (settings->width + 2) * 2);
	centralize_console();
	invisible_cursor();
	Plate* scoreFuild = new ScorePlate(settings->width + 2);
	Plate* fuild = new Fuild(settings->height + 2, settings->width + 2);
	srand(time(NULL));
	int i = rand() % 7;

	while (true) {
		if (i == 0)
		{
			boost::thread g(Tgame, settings, fuild);
			srand(time(NULL));
			i = rand() % 7;

			g.join();
		}
		if (fuild->gameover)
		{

			Sleep(3000);
			break;
		}
		worcker(fuild);
		if (i == 1)
		{
			boost::thread g(Linegame, settings, fuild);
			srand(time(NULL));
			i = rand() % 7;

			g.join();
		}
		if (fuild->gameover)
		{

			Sleep(3000);
			break;
		}
		worcker(fuild);
		if (i == 2)
		{
			boost::thread g(Lgame, settings, fuild);
			srand(time(NULL));
			i = rand() % 7;

			g.join();
		}
		if (fuild->gameover)
		{

			Sleep(3000);
			break;
		}
		worcker(fuild);
		if (i == 3)
		{
			boost::thread g(RLgame, settings, fuild);
			srand(time(NULL));
			i = rand() % 7;

			g.join();
		}
		if (fuild->gameover)
		{

			Sleep(3000);
			break;
		}
		worcker(fuild);
		if (i == 4)
		{
			boost::thread g(Zgame, settings, fuild);
			srand(time(NULL));
			i = rand() % 7;

			g.join();
		}
		if (fuild->gameover)
		{

			Sleep(3000);
			break;
		}
		worcker(fuild);
		if (i == 5)
		{
			boost::thread g(RZgame, settings, fuild);
			srand(time(NULL));
			i = rand() % 7;

			g.join();
		}
		if (fuild->gameover)
		{

			Sleep(3000);
			break;
		}
		worcker(fuild);
		if (i == 6)
		{
			boost::thread g(SQgame, settings, fuild);
			srand(time(NULL));
			i = rand() % 7;

			g.join();
		}
		if (fuild->gameover)
		{

			Sleep(3000);
			break;
		}
		worcker(fuild);
	}
	system("mode con cols=63 lines=34");
};