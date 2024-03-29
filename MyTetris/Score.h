#pragma once
#include <string>
#include <vector>
#include <fstream>
using namespace std;
struct Score
{
	vector<string> names;
	vector<int> points;
	void get_data_from_file()
	{
		ifstream in("score.txt");
		while (!in.eof())
		{
			string name;
			in >> name;
			int point;
			in >> point;
			names.push_back(name);
			points.push_back(point);
		}
		in.close();
	}
	void write_data_to_file()
	{
		ofstream out("score.txt");
		if (!out.is_open())
		{
			return;
		}
		for (int i = 0; i < names.size(); i++)
		{
			if (i != names.size() - 1)
			{
				out << names[i] << " " << points[i] << endl;
			}
			else
			{
				out << names[i] << " " << points[i];
			}
		}
		out.close();
	}
};