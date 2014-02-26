
#include "GameWindow.h"

int main()
{
    GameWindow* game_wind = new GameWindow(Config_file());
    game_wind->start();
}
