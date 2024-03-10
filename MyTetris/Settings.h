#pragma once
#include <string>
#include <fstream>
using namespace std;
struct Settings {
	int height;
	int width;
	string saving;
	int speed;
	unsigned int volume_of_music;
	unsigned int volume_of_sounds;
	int number_of_players;
	void standart_settings()
	{
		height = 25;
		width = 12;
		saving = "yes";
		speed = 2;
		number_of_players = 1;
		volume_of_music = 1000000000;
		volume_of_sounds = 1000000000;
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
			   >> number_of_players
			   >> volume_of_music >> volume_of_music;
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
			<< number_of_players << endl << volume_of_music
			<< endl << volume_of_sounds;
		out.close();
	}
	~Settings()
	{
		write_settings_to_file();
	}
};