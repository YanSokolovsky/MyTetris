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
drawerVisitor* drawer;
bool is_row_full(int i, Plate* fuild)
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
void delete_full_row(int i, Plate* fuild)
{
	for (int y = 1; y < fuild->width - 1; y++)
	{
		fuild->f[i][y].sq = "  ";

	}
}
void move_rows_down(int i, Plate* fuild)
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
void worker(Plate* fuild, Plate* plate)
{
	for (int i = 1; i < fuild->height - 1; i++)
	{
		if (is_row_full(i, fuild))
		{
			delete_full_row(i, fuild);
			move_rows_down(i, fuild);
			plate->pointsLine++;
		}
	}
	drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(plate));
}
void droping_of_brick(brick* t, Settings* settings, Plate* fuild, Plate* score)
{
	int i = 1000;
	while (true)
	{
		if (t->exist)
		{
			mut.lock();
			t->movedown();
			drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(score));
			mut.unlock();
		}
		else
		{
			return;
		}
		Sleep(i / settings->speed);
	}
}
void rotation_movement(brick* t, Settings* settings, Plate* fuild, Plate* score)
{
	while (t->exist)
	{
		if (GetAsyncKeyState(VK_UP)) {
			mut.lock();
			t->rotate();
			drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(score));
			mut.unlock();
			for (int i = 0; i < 15 && GetAsyncKeyState(VK_UP) & 0x8000; i++)
			{
				Sleep(10);
			}
			while (GetAsyncKeyState(VK_UP) && t->exist)
			{
				mut.lock();
				t->rotate();
				drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(score));
				mut.unlock();
				Sleep(90);
			}
		}
	}
}
void down_movement(brick* t, Settings* settings, Plate* fuild, Plate* score)
{
	while (t->exist)
	{
		if (GetAsyncKeyState(VK_DOWN)) {
			mut.lock();
			t->movedown();
			drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(score));
			mut.unlock();
			Sleep(100);
		}
	}
}
void movement_to_the_left(brick* t, Settings* settings, Plate* fuild, Plate* score)
{
	while (t->exist)
	{
		if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist) {
			mut.lock();
			t->moveleft();
			drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(score));
			mut.unlock();
			for (int i = 0; i < 15 && GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT); i++)
			{
				Sleep(10);
			}
			while (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				mut.lock();
				t->moveleft();
				drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(score));
				mut.unlock();
				Sleep(90);
			}
		}
	}
}
void movement_to_the_right(brick* t, Settings* settings, Plate* fuild, Plate* score)
{
	while (t->exist)
	{
		if (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT)) {
			mut.lock();
			t->moveright();
			drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(score));
			mut.unlock();
			for (int i = 0; i < 15 && !GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT); i++)
			{
				Sleep(10);
			}
			while (!GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_RIGHT) && t->exist)
			{
				mut.lock();
				t->moveright();
				drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(score));
				mut.unlock();
				Sleep(90);
			}
		}
	}
}
void Tgame(Settings* settings, Plate* fuild, Plate* plate)
{
	Tbrick* t = new Tbrick(fuild, settings->width / 2, 3);
	Tbrick* st = new Tbrick(plate, settings->width / 2, 2);
	st->position = t->position;
	st->drow();
	int i = 0;
	boost::thread th(droping_of_brick, (brick*)t, settings, fuild, plate);
	boost::thread th1(rotation_movement, (brick*)t, settings, fuild, plate);
	boost::thread th2(down_movement, (brick*)t, settings, fuild, plate);
	boost::thread th3(movement_to_the_left, (brick*)t, settings, fuild, plate);
	boost::thread th4(movement_to_the_right, (brick*)t, settings, fuild, plate);
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
			break;
		}
		else
		{
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			t->exist = false;
			fuild->gameover = true;
			return;
		}
	}
	ScorePlate* sp = static_cast<ScorePlate*>(plate);
	sp->clearing_plate();
	worker(fuild, plate);
}
void Linegame(Settings* settings, Plate* fuild, Plate* plate)
{
	Linebrick* t = new Linebrick(fuild, settings->width / 2, 3);
	Linebrick* st = new Linebrick(plate, settings->width / 2, 2);
	st->position = t->position;
	st->drow();
	int i = 0;
	boost::thread th(droping_of_brick, (brick*)t, settings, fuild, plate);
	boost::thread th1(rotation_movement, (brick*)t, settings, fuild, plate);
	boost::thread th2(down_movement, (brick*)t, settings, fuild, plate);
	boost::thread th3(movement_to_the_left, (brick*)t, settings, fuild, plate);
	boost::thread th4(movement_to_the_right, (brick*)t, settings, fuild, plate);
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
			worker(fuild, plate);
			break;
		}
		else
		{
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			t->exist = false;
			fuild->gameover = true;

			return;
		}
	}
	ScorePlate* sp = static_cast<ScorePlate*>(plate);
	sp->clearing_plate();
}
void Lgame(Settings* settings, Plate* fuild, Plate* plate)
{
	Lbrick* t = new Lbrick(fuild, settings->width / 2, 3);
	Lbrick* st = new Lbrick(plate, settings->width / 2, 2);
	st->position = t->position;
	st->drow();
	int i = 0;
	boost::thread th(droping_of_brick, (brick*)t, settings, fuild, plate);
	boost::thread th1(rotation_movement, (brick*)t, settings, fuild, plate);
	boost::thread th2(down_movement, (brick*)t, settings, fuild, plate);
	boost::thread th3(movement_to_the_left, (brick*)t, settings, fuild, plate);
	boost::thread th4(movement_to_the_right, (brick*)t, settings, fuild, plate);
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
			worker(fuild, plate);
			break;
		}
		else
		{
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			t->exist = false;
			fuild->gameover = true;
			return;
		}
	}
	ScorePlate* sp = static_cast<ScorePlate*>(plate);
	sp->clearing_plate();
}
void RLgame(Settings* settings, Plate* fuild, Plate* plate)
{
	RLbrick* t = new RLbrick(fuild, settings->width / 2, 3);
	RLbrick* st = new RLbrick(plate, settings->width / 2, 2);
	st->position = t->position;
	st->drow();
	int i = 0;
	boost::thread th(droping_of_brick, (brick*)t, settings, fuild, plate);
	boost::thread th1(rotation_movement, (brick*)t, settings, fuild, plate);
	boost::thread th2(down_movement, (brick*)t, settings, fuild, plate);
	boost::thread th3(movement_to_the_left, (brick*)t, settings, fuild, plate);
	boost::thread th4(movement_to_the_right, (brick*)t, settings, fuild, plate);
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
			worker(fuild, plate);
			break;
		}
		else
		{
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			t->exist = false;
			fuild->gameover = true;
			return;
		}
	}
	ScorePlate* sp = static_cast<ScorePlate*>(plate);
	sp->clearing_plate();
}
void Zgame(Settings* settings, Plate* fuild, Plate* plate)
{
	Zbrick* t = new Zbrick(fuild, settings->width / 2, 3);
	Zbrick* st = new Zbrick(plate, settings->width / 2, 2);
	st->position = t->position;
	st->drow();
	int i = 0;
	boost::thread th(droping_of_brick, (brick*)t, settings, fuild, plate);
	boost::thread th1(rotation_movement, (brick*)t, settings, fuild, plate);
	boost::thread th2(down_movement, (brick*)t, settings, fuild, plate);
	boost::thread th3(movement_to_the_left, (brick*)t, settings, fuild, plate);
	boost::thread th4(movement_to_the_right, (brick*)t, settings, fuild, plate);
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
			worker(fuild, plate);
			break;
		}
		else
		{
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			t->exist = false;
			fuild->gameover = true;
			return;
		}
	}
	ScorePlate* sp = static_cast<ScorePlate*>(plate);
	sp->clearing_plate();
}
void RZgame(Settings* settings, Plate* fuild, Plate* plate)
{
	RZbrick* t = new RZbrick(fuild, settings->width / 2, 3);
	RZbrick* st = new RZbrick(plate, settings->width / 2, 2);
	st->position = t->position;
	st->drow();
	int i = 0;
	boost::thread th(droping_of_brick, (brick*)t, settings, fuild, plate);
	boost::thread th1(rotation_movement, (brick*)t, settings, fuild, plate);
	boost::thread th2(down_movement, (brick*)t, settings, fuild, plate);
	boost::thread th3(movement_to_the_left, (brick*)t, settings, fuild, plate);
	boost::thread th4(movement_to_the_right, (brick*)t, settings, fuild, plate);
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
			worker(fuild, plate);
			break;
		}
		else
		{
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			t->exist = false;
			fuild->gameover = true;
			return;
		}
	}
	ScorePlate* sp = static_cast<ScorePlate*>(plate);
	sp->clearing_plate();
}
void SQgame(Settings* settings, Plate* fuild, Plate* plate)
{
	SQbrick* t = new SQbrick(fuild, settings->width / 2, 3);
	SQbrick* st = new SQbrick(plate, settings->width / 2, 2);
	st->position = t->position;
	st->drow();
	int i = 0;
	boost::thread th(droping_of_brick, (brick*)t, settings, fuild, plate);
	boost::thread th1(rotation_movement, (brick*)t, settings, fuild, plate);
	boost::thread th2(down_movement, (brick*)t, settings, fuild, plate);
	boost::thread th3(movement_to_the_left, (brick*)t, settings, fuild, plate);
	boost::thread th4(movement_to_the_right, (brick*)t, settings, fuild, plate);
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
			worker(fuild, plate);
			break;
		}
		else
		{
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			t->exist = false;
			fuild->gameover = true;
			return;
		}
	}
	ScorePlate* sp = static_cast<ScorePlate*>(plate);
	sp->clearing_plate();
}
void game_launch(Settings* settings, Score* score)
{
	set_console_size_by_chars(settings->height + 10, (settings->width + 2) * 2);
	centralize_console();
	invisible_cursor();
	Plate* scoreFuild = new ScorePlate(settings->width + 2);
	Plate* fuild = new Fuild(settings->height + 2, settings->width + 2);
	drawer = new drawerVisitor();
	drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(scoreFuild));
	srand(time(NULL));
	int i = rand() % 7;
	while (true) {
		i = rand() % 7;
		if (fuild->gameover)
		{
			break;
		}
		if (i == 0)
		{
			boost::thread g(Tgame, settings, fuild, scoreFuild);
			g.join();
			continue;
		}
		if (i == 1)
		{
			boost::thread g(Linegame, settings, fuild, scoreFuild);
			g.join();
			continue;
		}
		if (i == 2)
		{
			boost::thread g(Lgame, settings, fuild, scoreFuild);
			g.join();
			continue;
		}
		if (i == 3)
		{
			boost::thread g(RLgame, settings, fuild, scoreFuild);
			g.join();
			continue;
		}
		if (i == 4)
		{
			boost::thread g(Zgame, settings, fuild, scoreFuild);
			g.join();
			continue;
		}
		if (i == 5)
		{
			boost::thread g(RZgame, settings, fuild, scoreFuild);
			g.join();
			continue;
		}
		if (i == 6)
		{
			boost::thread g(SQgame, settings, fuild, scoreFuild);
			g.join();
			continue;
		}
	}
	clear_console();
	slow_drawer_from_file("gameover.txt");
	Sleep(1000);
	if (settings->saving == "yes")
	{
		Sleep(1000);
		cout << "Enter your name hiro, that plays this game." << endl;
		string name;
		cin >> name;
		score->names.push_back(name);
		score->points.push_back(scoreFuild->pointsLine);
	}
};