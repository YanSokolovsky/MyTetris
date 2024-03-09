#include "StartScene.h"

#include <iostream>
#include <windows.h>
#include <boost/thread.hpp>
int main()
{
    boost::thread t(start_menu_launch);
    t.join();
    return 0;
}
