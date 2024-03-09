#include "SettingsScene.h"
#include "ConsoleFunctions.h"
#include "settings.h"

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <vector>
#include <limits>
using namespace std;

void draw_condition(Settings* settings, int i)
{
	clear_IObuffer();
	clear_console();
	move_cursore_topleft();
	string high = "\n                                                              \n";
	string line = "                                                              \n";
	std::cout << high;
	string set1 = "   high of the fuild:  ";
	string end1 = "   ";
	string e1 = "<<<";
	string set2 = "   windth of th fuild:  ";
	string end2 = "   ";
	string e2 = "<<<";
	string set3 = "   saving of score:  ";
	string end3 = "   ";
	string e3 = "<<<";
	string set4 = "   speed of bricks:  ";
	string end4 = "   ";
	string e4 = "<<<";



	switch (i)
	{
	//case -1: cout << setting1 + end1 << endl << line << setting2 + end2 << endl << line << setting3 + end3 << endl << line << setting4 + end4 << endl << line << slow_drawer_from_file("set.txt"); break;
	//case 0: cout << setting1 + e1 << endl << line << setting2 + end2 << endl << line << setting3 + end3 << endl << line << setting4 + end4 << endl << line << slow_drawer_from_file("set.txt"); break;
	//case 1: cout << setting1 + end1 << endl << line << setting2 + e2 << endl << line << setting3 + end3 << endl << line << setting4 + end4 << endl << line << slow_drawer_from_file("set.txt"); break;
	//case 2: cout << setting1 + end1 << endl << line << setting2 + end2 << endl << line << setting3 + e3 << endl << line << setting4 + end4 << endl << line << slow_drawer_from_file("set.txt"); break;
	//case 3: cout << setting1 + end1 << endl << line << setting2 + end2 << endl << line << setting3 + end3 << endl << line << setting4 + e4 << endl << line << slow_drawer_from_file("set.txt"); break;
	}
};
void settings_menu_launch(Settings* settings)
{
	int button = 10000;
	draw_condition(settings, -1);
	while (true)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			button--;
			draw_condition(settings, button % 7);
			for (int i = 0; i < 15 && GetAsyncKeyState(VK_UP) & 0x8000; i++)
			{
				Sleep(10);
			}
			while (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				button--;
				draw_condition(settings, button % 7);
				Sleep(90);
			}
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			return;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			button++;
			draw_condition(settings, button % 7);
			for (int i = 0; i < 15 && GetAsyncKeyState(VK_DOWN) & 0x8000; i++)
			{
				Sleep(10);
			}
			while (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				button++;
				draw_condition(settings, button % 7);
				Sleep(90);
			}
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			switch (button % 7)
			{
			case 0: 
				if (settings->height < 51 && settings->height > 9)
				settings->height++;
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_RIGHT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_RIGHT) & 0x8000 && settings->height <= 50 && settings->height > 9)
				{
					settings->height++;
					draw_condition(settings, button % 7);
					Sleep(90);
				}
				break;
			case 1:
				if (settings->width < 20 && settings->width > 5)
					settings->width++;
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_RIGHT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_RIGHT) & 0x8000 && settings->width <= 20 && settings->height > 5)
				{
					settings->width++;
					draw_condition(settings, button % 7);
					Sleep(90);
				}
				break;
			case 2:
				if (settings->saving == "yes")
				{
					settings->saving = "no";
				}
				else
				{
					settings->saving = "yes";
				}
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_RIGHT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_RIGHT) & 0x8000)
				{
					if (settings->saving == "yes")
					{
						settings->saving = "no";
					}
					else
					{
						settings->saving = "yes";
					}
					draw_condition(settings, button % 7);
					Sleep(90);
				}
				break;
			case 3:
				if (settings->speed <= 10 && settings->speed > 0)
					settings->speed++;
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_RIGHT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_RIGHT) & 0x8000 && settings->speed <= 10 && settings->speed > 0)
				{
					settings->speed++;
					draw_condition(settings, button % 7);
					Sleep(90);
				}
				break;
			case 4:break;
			case 5:break;
			case 6:break;
			default:
				break;
			}
			for (int i = 0; i < 15 && GetAsyncKeyState(VK_DOWN) & 0x8000; i++)
			{
				Sleep(10);
			}
			while (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				button++;
				draw_condition(settings, button % 7);
				Sleep(90);
			}
		}
	}
};