#pragma once
#include <vector>
#include <ctime>
#include <graphics.h>
#include "Plant.h"
#include "Zombie.h"
#include "Bullet.h"

class Game {
private:
    int sunNum;
    std::vector<Plant*> plantList;
    std::vector<Zombie*> zombieList;
    std::vector<Bullet*> bulletList;

    clock_t lastZombieSpawnTime;
    clock_t gameStartTime;
    bool isGameOver;
    bool isWin;

    IMAGE bg;       // 地图背景
    bool hasBg;     // 地图是否加载成功

public:
    Game();
    ~Game();

    void GameLoop();
    void UpdateObjects();
    void CheckCollision();
    void CleanUpDeadObjects();
    void DrawObjects();
    void HandleInput();
    void JudgeWinOrLose();

    bool IsWin() const;
    bool IsGameOver() const;
};