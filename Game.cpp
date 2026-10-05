#include "Game.h"
#include <graphics.h>

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 600;

// ================= 构造函数 =================
Game::Game() {
    sunNum = 150;
    lastZombieSpawnTime = clock();
    gameStartTime = clock();
    isGameOver = false;
    isWin = false;

    // 加载地图背景
    loadimage(&bg, _T("res/background.png"), WINDOW_WIDTH, WINDOW_HEIGHT, true);
    hasBg = (bg.getwidth() > 0);
}

// ================= 析构函数 =================
Game::~Game() {
    for (auto p : plantList) delete p;
    for (auto z : zombieList) delete z;
    for (auto b : bulletList) delete b;
}

// ================= 游戏主循环 =================
void Game::GameLoop() {
    BeginBatchDraw();

    while (!isGameOver) {
        // 1. 绘制地图背景
        if (hasBg) {
            putimage(0, 0, &bg);
        }
        else {
            setbkcolor(RGB(200, 230, 200));
            cleardevice();
        }

        // 2. 逻辑更新
        UpdateObjects();
        CheckCollision();
        JudgeWinOrLose();

        // 3. 绘制所有对象
        DrawObjects();

        // 4. 处理鼠标输入
        HandleInput();

        FlushBatchDraw();
        Sleep(16);
    }

    EndBatchDraw();
}

// ================= 更新所有对象 =================
void Game::UpdateObjects() {
    // 每 2 秒生成一个僵尸
    if (clock() - lastZombieSpawnTime > 2 * CLOCKS_PER_SEC) {
        zombieList.push_back(new Zombie(850, 100 + rand() % 4 * 100));
        lastZombieSpawnTime = clock();
    }

    // 更新植物，随机发射子弹
    for (auto p : plantList) {
        p->Update();
        if (rand() % 100 == 0) {
            Bullet* b = p->Attack();
            if (b) bulletList.push_back(b);
        }
    }

    // 更新僵尸和子弹
    for (auto z : zombieList) z->Update();
    for (auto b : bulletList) b->Update();

    CleanUpDeadObjects();
}

// ================= 碰撞检测 =================
void Game::CheckCollision() {
    // 1. 子弹 vs 僵尸
    for (auto b : bulletList) {
        if (b->IsDead()) continue;
        for (auto z : zombieList) {
            if (z->IsDead()) continue;

            RECT r1 = b->GetRect();
            RECT r2 = z->GetRect();
            if (r1.left < r2.right && r1.right > r2.left &&
                r1.top < r2.bottom && r1.bottom > r2.top) {
                b->ReduceHP(100);
                z->ReduceHP(20);
                break;
            }
        }
    }

    // 2. 僵尸 vs 植物（啃食）
    for (auto z : zombieList) {
        if (z->IsDead()) continue;
        for (auto p : plantList) {
            if (p->IsDead()) continue;

            RECT r1 = z->GetRect();
            RECT r2 = p->GetRect();
            if (r1.left < r2.right && r1.right > r2.left &&
                r1.top < r2.bottom && r1.bottom > r2.top) {
                z->Bite(p);
            }
        }
    }
}

// ================= 清理死亡对象 =================
void Game::CleanUpDeadObjects() {
    for (auto it = plantList.begin(); it != plantList.end(); ) {
        if ((*it)->IsDead()) { delete* it; it = plantList.erase(it); }
        else ++it;
    }
    for (auto it = zombieList.begin(); it != zombieList.end(); ) {
        if ((*it)->IsDead()) { delete* it; it = zombieList.erase(it); }
        else ++it;
    }
    for (auto it = bulletList.begin(); it != bulletList.end(); ) {
        if ((*it)->IsDead()) { delete* it; it = bulletList.erase(it); }
        else ++it;
    }
}

// ================= 绘制所有对象 =================
void Game::DrawObjects() {
    for (auto p : plantList) p->Draw();
    for (auto z : zombieList) z->Draw();
    for (auto b : bulletList) b->Draw();

    // UI 文字
    settextcolor(BLACK);
    settextstyle(20, 0, _T("微软雅黑"));

    TCHAR sunText[50];
    _stprintf_s(sunText, 50, _T("Sun: %d"), sunNum);
    outtextxy(10, 10, sunText);

    outtextxy(10, 40, _T("Left Click to Plant (Cost 50)"));
}

// ================= 鼠标输入 =================
void Game::HandleInput() {
    if (MouseHit()) {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            if (sunNum >= 50 && msg.y > 80 && msg.y < 500) {
                plantList.push_back(new Plant(msg.x, msg.y));
                sunNum -= 50;
            }
        }
    }
}

// ================= 胜负判定 =================
void Game::JudgeWinOrLose() {
    // 失败：僵尸到最左边
    for (auto z : zombieList) {
        if (z->GetX() <= 0) {
            isWin = false;
            isGameOver = true;
            break;
        }
    }

    // 胜利：开局 5 秒后僵尸全清空
    if (zombieList.empty() && clock() - gameStartTime > 5 * CLOCKS_PER_SEC) {
        isWin = true;
        isGameOver = true;
    }
}

bool Game::IsWin() const { return isWin; }
bool Game::IsGameOver() const { return isGameOver; }