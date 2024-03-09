#include "Score.h"
#include "ScoreScene.h"

#include <windows.h>
#include <iostream>
#include <iomanip>

void score_menu_launch(Score* score)
{
    score->names = vector<string>();
    score->points = vector<int>();
    score->get_data_from_file();
    for (int i = 0; i < score->names.size(); i++)
    {
        cout << "---------------------------------------------------\n";
        cout << "|" << std::setw(25) << score->names[i]
             << score->points[i] << std::setw(0) << "|" << endl;
        cout << "---------------------------------------------------\n";
    }
    while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000));
    return;
}