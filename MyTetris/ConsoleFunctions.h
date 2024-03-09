#pragma once
#include <windows.h>
void invisible_cursor();
void clear_console();
void move_cursore_topleft();
void set_colors(int background, int textColor);
void set_console_size_by_chars(int rows, int columns);
int get_pixel_console_width();
int get_pixel_console_height();
int get_pixel_screen_width();
int get_pixel_screen_height();
void centralize_console();