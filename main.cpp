#include <graphics.h>
#include <ctime>
#include "Game.h"

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 600;

int main() {
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
    srand((unsigned int)time(NULL));

    Game game;
    game.GameLoop();

    settextcolor(BLACK);
    settextstyle(40, 0, _T("微软雅黑"));
    if (game.IsWin()) {
        outtextxy(WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2, _T("You Win!"));
    }
    else {
        outtextxy(WINDOW_WIDTH / 2 - 110, WINDOW_HEIGHT / 2, _T("Game Over!"));
    }

    Sleep(3000);
    closegraph();
    return 0;
}