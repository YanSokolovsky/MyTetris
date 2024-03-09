#include "ConsoleFunctions.h"
#include "Settings.h"
#include "Score.h"
#include "ScoreScene.h"

#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <boost/thread.hpp>
using namespace std;
void write(string sceneState)
{
	invisible_cursor();
	move_cursore_topleft();
	cout << sceneState;
};
string animation_loader(string filename)
{
    string line;
    string resline;
    ifstream in(filename);
    if (in.is_open()) {
        while (getline(in, line)) {
            resline += line + "\n";
        }
    }
    in.close();
    return resline;
};
void selector(int i)
{
	i = i % 3;
	switch (i)
	{
	case 0: write(animation_loader("start0.txt")); break;
	case 1: write(animation_loader("start1.txt")); break;
	case 2: write(animation_loader("start2.txt")); break;
	}
};
void start_menu_launch()
{
	invisible_cursor();
	Settings* settings = new Settings();
	settings->get_settings_from_file();
	Score* score = new Score();
	int button = 102;
	char key;
	set_console_size_by_chars(34, 63);
	write(animation_loader("start.txt"));
	while (true)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			selector(button);
			for (int i = 0; i < 15 && GetAsyncKeyState(VK_UP) & 0x8000; i++)
			{
				Sleep(10);
			}
			while (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				button--;
				selector(button);
				Sleep(90);
			}
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			selector(button);
			for (int i = 0; i < 15 && GetAsyncKeyState(VK_DOWN) & 0x8000; i++)
			{
				Sleep(10);
			}
			while (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				button++;
				Sleep(90);
				selector(button);
			}
		}
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			clear_console();
			move_cursore_topleft();
			invisible_cursor();
			if (button % 3 == 0) {
				boost::thread t(startgame, settings, score);
				t.join();
				set_console_size_by_chars(34, 63);
			}
			if (button % 3 == 1) {
				boost::thread t(operateset, settings);
				t.join();
				set_console_size_by_chars(34, 63);
			}
			if (button % 3 == 2) {
				boost::thread t(score_menu_launch, score);
				t.join();
				set_console_size_by_chars(34, 63);
			}
			selector(button);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			break;
		}
	}
};