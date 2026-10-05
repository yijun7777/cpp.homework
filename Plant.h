#pragma once
#include "GameObject.h"
#include "Bullet.h"

class Plant : public GameObject {
private:
    int sunCost;
    int attackTime;  // 攻击间隔（帧数）
    int counter;     // 帧计数器

public:
    Plant(int _x, int _y);

    void Draw() override;
    void Update() override;

    Bullet* Attack();

    int GetSunCost() const;
};