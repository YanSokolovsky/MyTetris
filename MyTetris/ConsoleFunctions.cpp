#include <windows.h>
void invisible_cursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void clear_screen() {
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