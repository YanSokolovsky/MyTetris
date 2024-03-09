#include"ConsoleFunctions.h"
#include <windows.h>
#include <string>

void invisible_cursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void clear_console() {
	char fill = ' ';
	COORD topLeft = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, topLeft, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, topLeft, &written);
	SetConsoleCursorPosition(console, topLeft);
}

void move_cursore_topleft()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD topLeft = { 0,0 };
	SetConsoleCursorPosition(console, topLeft);
}

void set_colors(int background, int textColor)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, background | textColor);
}

void set_console_size_by_chars(int rows, int columns)
{
	std::string strBeforParam1 = "mode con cols=";
	std::string param1 = std::to_string(columns);
	std::string strBeforParam2 = " lines=";
	std::string param2 = std::to_string(rows);
	system((strBeforParam1 + param1 + strBeforParam2 + param2).c_str());
}

int get_pixel_console_width()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(ConsoleHandle, &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int get_pixel_console_height()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(ConsoleHandle, &csbi);
	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

int get_pixel_screen_width()
{
	return GetSystemMetrics(SM_CXSCREEN);
}

int get_pixel_screen_height()
{
	return GetSystemMetrics(SM_CYSCREEN);
}

void centralize_console()
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow,
				 HWND_TOP,
				 get_pixel_screen_width() / 2 - get_pixel_console_width() / 2,
				 get_pixel_screen_height() / 2 - get_pixel_console_height() / 2,
				 get_pixel_screen_width(),
				 get_pixel_screen_height(),
				 NULL);
	return;
}