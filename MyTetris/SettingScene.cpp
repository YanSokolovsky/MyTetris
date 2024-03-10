#include "SettingsScene.h"
#include "ConsoleFunctions.h"
#include "Settings.h"
#include "SettingsScene.h"

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <vector>
#include <string>
#include <limits>
using namespace std;

void draw_condition(Settings* settings, int i)
{
	move_cursore_topleft();
	invisible_cursor();
	string emptyLine = "                                                    \n";
	string markingLine = "----------------------------------------------------\n";
	string settingHeight = "  height of the game fuild   " + to_string(settings->height) + "    \n";
	string settingWidth = "  width of the game fuild   " + to_string(settings->width) + "    \n";
	string settingSaving = "  would you like to save your achievements   " + settings->saving + "    \n";
	string settingSpeed = "  speed of blocks   " + to_string(settings->speed) + "    \n";
	string settingPlayers = "  number of players   " + to_string(settings->number_of_players) + "    \n";
	string settingMusic = "  volume of music in game   " + to_string(settings->volume_of_music / 10000000) + "%    \n";
	string settingSounds = "  volume of sounds   " + to_string(settings->volume_of_sounds / 10000000) + "%    \n";
	switch (i)
	{
	case -1: 
		cout 
		<< emptyLine << emptyLine
		<< settingHeight
		<< emptyLine << emptyLine
		<< settingWidth
		<< emptyLine << emptyLine
		<< settingSaving
		<< emptyLine << emptyLine
		<< settingSpeed
		<< emptyLine << emptyLine
		<< settingMusic
		<< emptyLine << emptyLine
		<< settingSounds
		<< emptyLine << emptyLine
		<< settingPlayers
		<< emptyLine << emptyLine; break;
	case 0:
		cout
			<< emptyLine << markingLine
			<< settingHeight
			<< markingLine << emptyLine
			<< settingWidth
			<< emptyLine << emptyLine
			<< settingSaving
			<< emptyLine << emptyLine
			<< settingSpeed
			<< emptyLine << emptyLine
			<< settingMusic
			<< emptyLine << emptyLine
			<< settingSounds
			<< emptyLine << emptyLine
			<< settingPlayers
			<< emptyLine << emptyLine;break;
	case 1:
		cout
		<< emptyLine << emptyLine
		<< settingHeight
		<< emptyLine << markingLine
		<< settingWidth
		<< markingLine << emptyLine
		<< settingSaving
		<< emptyLine << emptyLine
		<< settingSpeed
		<< emptyLine << emptyLine
		<< settingMusic
		<< emptyLine << emptyLine
		<< settingSounds
		<< emptyLine << emptyLine
		<< settingPlayers
		<< emptyLine << emptyLine; break;
	case 2:
		cout
		<< emptyLine << emptyLine
		<< settingHeight
		<< emptyLine << emptyLine
		<< settingWidth
		<< emptyLine << markingLine
		<< settingSaving
		<< markingLine << emptyLine
		<< settingSpeed
		<< emptyLine << emptyLine
		<< settingMusic
		<< emptyLine << emptyLine
		<< settingSounds
		<< emptyLine << emptyLine
		<< settingPlayers
		<< emptyLine << emptyLine; break;
	case 3:
		cout
		<< emptyLine << emptyLine
		<< settingHeight
		<< emptyLine << emptyLine
		<< settingWidth
		<< emptyLine << emptyLine
		<< settingSaving
		<< emptyLine << markingLine
		<< settingSpeed
		<< markingLine << emptyLine
		<< settingMusic
		<< emptyLine << emptyLine
		<< settingSounds
		<< emptyLine << emptyLine
		<< settingPlayers
		<< emptyLine << emptyLine; break;
	case 4:
		cout
		<< emptyLine << emptyLine
		<< settingHeight
		<< emptyLine << emptyLine
		<< settingWidth
		<< emptyLine << emptyLine
		<< settingSaving
		<< emptyLine << emptyLine
		<< settingSpeed
		<< emptyLine << markingLine
		<< settingMusic
		<< markingLine << emptyLine
		<< settingSounds
		<< emptyLine << emptyLine
		<< settingPlayers
		<< emptyLine << emptyLine; break;
	case 5:
		cout
		<< emptyLine << emptyLine
		<< settingHeight
		<< emptyLine << emptyLine
		<< settingWidth
		<< emptyLine << emptyLine
		<< settingSaving
		<< emptyLine << emptyLine
		<< settingSpeed
		<< emptyLine << emptyLine
		<< settingMusic
		<< emptyLine << markingLine
		<< settingSounds
		<< markingLine << emptyLine
		<< settingPlayers
		<< emptyLine << emptyLine; break;
	case 6:
		cout
		<< emptyLine << emptyLine
		<< settingHeight
		<< emptyLine << emptyLine
		<< settingWidth
		<< emptyLine << emptyLine
		<< settingSaving
		<< emptyLine << emptyLine
		<< settingSpeed
		<< emptyLine << emptyLine
		<< settingMusic
		<< emptyLine << emptyLine
		<< settingSounds
		<< emptyLine << markingLine
		<< settingPlayers
		<< markingLine << emptyLine; break;
	}
};
void settings_menu_launch(Settings* settings)
{
	int button = 700;
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
				if (settings->height < 50)
				settings->height++;
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_RIGHT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_RIGHT) & 0x8000 && settings->height < 50)
				{
					settings->height++;
					draw_condition(settings, button % 7);
					Sleep(90);
				}
				break;
			case 1:
				if (settings->width < 20)
					settings->width++;
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_RIGHT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_RIGHT) & 0x8000 && settings->width < 20)
				{
					settings->width++;
					draw_condition(settings, button % 7);
					Sleep(90);
				}
				break;
			case 2:
				if (settings->saving == "yes")
				{
					settings->saving = "no ";
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
						settings->saving = "no ";
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
				if (settings->speed < 10)
					settings->speed++;
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_RIGHT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_RIGHT) & 0x8000 && settings->speed < 10)
				{
					settings->speed++;
					draw_condition(settings, button % 7);
					Sleep(90);
				}
				break;
			case 4:
				if (settings->volume_of_music < 1000000000)
					settings->volume_of_music += 10000000;
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_RIGHT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_RIGHT) & 0x8000 && settings->volume_of_music < 1000000000)
				{
					settings->volume_of_music += 10000000;
					draw_condition(settings, button % 7);
					Sleep(40);
				}
				break;
			case 5:
				if (settings->volume_of_sounds < 1000000000)
					settings->volume_of_sounds += 10000000;
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_RIGHT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_RIGHT) & 0x8000 && settings->volume_of_sounds < 1000000000)
				{
					settings->volume_of_sounds += 10000000;
					draw_condition(settings, button % 7);
					Sleep(40);
				}
				break;
			case 6:
				if (settings->number_of_players == 2)
				{
					settings->number_of_players = 1;
				}
				else
				{
					settings->number_of_players = 2;
				}
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_RIGHT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_RIGHT) & 0x8000)
				{
					if (settings->number_of_players == 2)
					{
						settings->number_of_players = 1;
					}
					else
					{
						settings->number_of_players = 2;
					}
					draw_condition(settings, button % 7);
					Sleep(90);
				};
				break;
			default:
				break;
			}
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			switch (button % 7)
			{
			case 0:
				if (settings->height > 10)
					settings->height--;
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_LEFT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_LEFT) & 0x8000 && settings->height > 10)
				{
					settings->height--;
					draw_condition(settings, button % 7);
					Sleep(90);
				}
				break;
			case 1:
				if (settings->width > 5)
					settings->width--;
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_LEFT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_LEFT) & 0x8000 && settings->width > 5)
				{
					settings->width--;
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
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_LEFT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_LEFT) & 0x8000)
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
				if (settings->speed > 1)
					settings->speed--;
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_LEFT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_LEFT) & 0x8000 && settings->speed > 1)
				{
					settings->speed--;
					draw_condition(settings, button % 7);
					Sleep(90);
				}
				break;
			case 4:
				if (settings->volume_of_music > 0)
					settings->volume_of_music -= 10000000;
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_LEFT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_LEFT) & 0x8000 && settings->volume_of_music > 0)
				{
					settings->volume_of_music -= 10000000;
					draw_condition(settings, button % 7);
					Sleep(40);
				}
				break;
			case 5:
				if (settings->volume_of_sounds > 0)
				settings->volume_of_sounds -= 10000000;
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_LEFT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_LEFT) & 0x8000 && settings->volume_of_sounds > 0)
				{
					settings->volume_of_sounds -= 10000000;
					draw_condition(settings, button % 7);
					Sleep(40);
				}
				break;
			case 6:
				if (settings->number_of_players == 2)
				{
					settings->number_of_players = 1;
				}
				else
				{
					settings->number_of_players = 2;
				}
				draw_condition(settings, button % 7);
				for (int i = 0; i < 15 && GetAsyncKeyState(VK_LEFT) & 0x8000; i++)
				{
					Sleep(10);
				}
				while (GetAsyncKeyState(VK_LEFT) & 0x8000)
				{
					if (settings->number_of_players == 2)
					{
						settings->number_of_players = 1;
					}
					else
					{
						settings->number_of_players = 2;
					}
					draw_condition(settings, button % 7);
					Sleep(90);
				};
				break;
			default:
				break;
			}
		}
	}
};