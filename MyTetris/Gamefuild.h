#pragma once
#include "Settings.h"
#include "Score.h"
#include "Squer.h"
#include "StartScene.h"
#include "Brick_controllers.h"

#include <string>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>
using namespace std;
boost::mutex  lrmut;
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
void Tgame(Settings* settings, Plate* fuild, Plate* plate, int x, int y)
{
	Tbrick* t = new Tbrick(fuild, x, y);
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
		if (i == 3)
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
void Linegame(Settings* settings, Plate* fuild, Plate* plate, int x, int y)
{
	Linebrick* t = new Linebrick(fuild, x, y);
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
		if (i == 3)
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
void Lgame(Settings* settings, Plate* fuild, Plate* plate, int x, int y)
{
	Lbrick* t = new Lbrick(fuild, x, y);
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
		if (i == 3)
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
void RLgame(Settings* settings, Plate* fuild, Plate* plate, int x, int y)
{
	RLbrick* t = new RLbrick(fuild, x, y);
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
		if (i == 3)
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
void Zgame(Settings* settings, Plate* fuild, Plate* plate, int x, int y)
{
	Zbrick* t = new Zbrick(fuild, x, y);
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
		if (i == 3)
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
void RZgame(Settings* settings, Plate* fuild, Plate* plate, int x, int y)
{
	RZbrick* t = new RZbrick(fuild, x, y);
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
		if (i == 3)
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
void SQgame(Settings* settings, Plate* fuild, Plate* plate, int x, int y)
{
	SQbrick* t = new SQbrick(fuild, x, y);
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
		if (i == 3)
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
void draw_next_brick(int i, Plate* scorePlate, Settings* settings)
{
	if (i == 0)
	{
		Tbrick* t = new Tbrick(scorePlate, settings->width / 2, 2);
		t->position = 0;
		t->drow();
	}
	if (i == 1)
	{
		Linebrick* t = new Linebrick(scorePlate, settings->width / 2, 2);
		t->position = 0;
		t->drow();
	}
	if (i == 2)
	{
		Lbrick* t = new Lbrick(scorePlate, settings->width / 2, 2);
		t->position = 0;
		t->drow();
	}
	if (i == 3)
	{
		RLbrick* t = new RLbrick(scorePlate, settings->width / 2, 2);
		t->position = 0;
		t->drow();
	}
	if (i == 4)
	{
		Zbrick* t = new Zbrick(scorePlate, settings->width / 2, 2);
		t->position = 0;
		t->drow();
	}
	if (i == 5)
	{
		RZbrick* t = new RZbrick(scorePlate, settings->width / 2, 2);
		t->position = 0;
		t->drow();
	}
	if (i == 6)
	{
		SQbrick* t = new SQbrick(scorePlate, settings->width / 2, 2);
		t->position = 0;
		t->drow();
	}
}
void game_launch(Settings* settings, Score* score)
{
	
	waveOutSetVolume(0, settings->volume_of_music | settings->volume_of_music << 16);
	PlaySoundA("tetris2.wav", NULL, SND_LOOP | SND_ASYNC);

	set_console_size_by_chars(settings->height + 10, (settings->width + 2) * 2);
	centralize_console();
	invisible_cursor();
	Plate* scoreFuild = new ScorePlate(settings->width + 2);
	Plate* fuild = new Fuild(settings->height + 2, settings->width + 2);
	drawer = new drawerVisitor();
	drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(scoreFuild));
	srand(time(NULL));
	int current = rand() % 7;
	int next;
	while (true) {
		srand(time(NULL));
		next = rand() % 7;
		draw_next_brick(next, scoreFuild, settings);
		if (fuild->gameover)
		{
			break;
		}
		if (current == 0)
		{
			boost::thread g(Tgame, settings, fuild, scoreFuild, fuild->width / 2, 3);
			g.join();
			current = next;
			continue;
		}
		if (current == 1)
		{
			boost::thread g(Linegame, settings, fuild, scoreFuild, fuild->width / 2, 3);
			g.join();
			current = next;
			continue;
		}
		if (current == 2)
		{
			boost::thread g(Lgame, settings, fuild, scoreFuild, fuild->width / 2, 3);
			g.join();
			current = next;
			continue;
		}
		if (current == 3)
		{
			boost::thread g(RLgame, settings, fuild, scoreFuild, fuild->width / 2, 3);
			g.join();
			current = next;
			continue;
		}
		if (current == 4)
		{
			boost::thread g(Zgame, settings, fuild, scoreFuild, fuild->width / 2, 3);
			g.join();
			current = next;
			continue;
		}
		if (current == 5)
		{
			boost::thread g(RZgame, settings, fuild, scoreFuild, fuild->width / 2, 3);
			g.join();
			current = next;
			continue;
		}
		if (current == 6)
		{
			boost::thread g(SQgame, settings, fuild, scoreFuild, fuild->width / 2, 3);
			g.join();
			current = next;
			continue;
		}
	}
	
	PlaySound(NULL, NULL, 0);

	clear_console();
	set_console_size_by_chars(40, 70);
	std::cout << slow_drawer_from_file("gameover.txt");
	Sleep(1000);
	clear_console();
	if (settings->saving == "yes" && settings->number_of_players != 2)
	{
		Sleep(1000);
		std::cout << "Enter your name hiro, that plays this game." << endl;
		string name;
		std::cin >> name;
		score->names.push_back(name);
		score->points.push_back(scoreFuild->pointsLine);
		score->write_data_to_file();
	}
};