#include "Score.h"
#include "ScoreScene.h"

#include <windows.h>
#include <iostream>
#include <iomanip>

void score_menu_launch(Score* score)
{
    for (int i = 0; i < score->names.size(); i++)
    {
        cout << " --------------------------------------------------\n";
        cout << "|" << std::setw(17) << score->names[i] << std::setw(17)
             << score->points[i] << std::setw(17) << "|" << endl;
        cout << " --------------------------------------------------\n";
    }
    while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000));
    return;
}