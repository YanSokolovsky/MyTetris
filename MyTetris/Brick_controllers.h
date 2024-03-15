#pragma once
#include "Plates.h"
#include "Settings.h"
#include "Bricks.h"

#include <boost/thread/mutex.hpp>
#include <windows.h>
boost::mutex mut;
drawerVisitor* drawer;
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
		if (GetAsyncKeyState(0x25) && !GetAsyncKeyState(VK_RIGHT) && t->exist) {
			mut.lock();
			t->moveleft();
			drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(score));
			mut.unlock();
			for (int i = 0; i < 15 && GetAsyncKeyState(0x25) && !GetAsyncKeyState(VK_RIGHT); i++)
			{
				Sleep(10);
			}
			while (GetAsyncKeyState(0x25) && !GetAsyncKeyState(VK_RIGHT) && t->exist)
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
		if (!GetAsyncKeyState(0x25) && GetAsyncKeyState(VK_RIGHT)) {
			mut.lock();
			t->moveright();
			drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(score));
			mut.unlock();
			for (int i = 0; i < 15 && !GetAsyncKeyState(0x25) && GetAsyncKeyState(VK_RIGHT); i++)
			{
				Sleep(10);
			}
			while (!GetAsyncKeyState(0x25) && GetAsyncKeyState(VK_RIGHT) && t->exist)
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
//------------------------------------------------------------------------------------------------
void rotation_movement2(brick* t, Settings* settings, Plate* fuild, Plate* score)
{
	while (t->exist)
	{
		if (GetAsyncKeyState(0x57)) {
			mut.lock();
			t->rotate();
			drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(score));
			mut.unlock();
			for (int i = 0; i < 15 && GetAsyncKeyState(0x57) & 0x8000; i++)
			{
				Sleep(10);
			}
			while (GetAsyncKeyState(0x57) && t->exist)
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
void down_movement2(brick* t, Settings* settings, Plate* fuild, Plate* score)
{
	while (t->exist)
	{
		if (GetAsyncKeyState(0x53)) {
			mut.lock();
			t->movedown();
			drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(score));
			mut.unlock();
			Sleep(100);
		}
	}
}
void movement_to_the_left2(brick* t, Settings* settings, Plate* fuild, Plate* score)
{
	while (t->exist)
	{
		if (GetAsyncKeyState(0x41) && !GetAsyncKeyState(0x44) && t->exist) {
			mut.lock();
			t->moveleft();
			drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(score));
			mut.unlock();
			for (int i = 0; i < 15 && GetAsyncKeyState(0x41) && !GetAsyncKeyState(0x44); i++)
			{
				Sleep(10);
			}
			while (GetAsyncKeyState(0x41) && !GetAsyncKeyState(0x44) && t->exist)
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
void movement_to_the_right2(brick* t, Settings* settings, Plate* fuild, Plate* score)
{
	while (t->exist)
	{
		if (!GetAsyncKeyState(0x41) && GetAsyncKeyState(0x44)) {
			mut.lock();
			t->moveright();
			drawer->draw(static_cast<Fuild*>(fuild), static_cast<ScorePlate*>(score));
			mut.unlock();
			for (int i = 0; i < 15 && !GetAsyncKeyState(0x41) && GetAsyncKeyState(0x44); i++)
			{
				Sleep(10);
			}
			while (!GetAsyncKeyState(0x41) && GetAsyncKeyState(0x44) && t->exist)
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