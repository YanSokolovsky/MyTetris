#pragma once
#include <string>
#include <fstream>
using namespace std;
struct Settings {
	int height;
	int width;
	std::string saving;
	int speed;
	int volume_of_music;
	int volume_of_sounds;
	int number_of_players;
	void standart_settings()
	{
		height = 25;
		width = 12;
		saving = "yes";
		speed = 2;
		number_of_players = 1;
	}
	void get_settings_from_file()
	{
		ifstream in("settings.txt");
		if (in.eof())
		{
			standart_settings();
		}
		else
		{
			in >> height >> width
			   >> saving >> speed
			   >> number_of_players;
		}
		in.close();
	}
	void write_settings_to_file() const
	{
		ofstream out("settings.txt");
		if (out.is_open()) {
			return;
		}
		out << height << endl << width << endl
			<< saving << endl << speed << endl
			<< number_of_players;
		out.close();
	}
	~Settings()
	{
		write_settings_to_file();
	}
};