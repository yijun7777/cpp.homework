#include "Zombie.h"

Zombie::Zombie(int _x, int _y)
    : GameObject(_x, _y, 100), speed(2), attackCounter(0) {
    LoadImage(_T("res/zombie.png"), 60, 60);
}

void Zombie::Draw() {
    if (hasImage) {
        putimage(x, y, &img);
    }
    else {
        setfillcolor(RED);
        solidrectangle(x, y, x + 40, y + 40);
    }
}

void Zombie::Update() {
    if (IsDead()) return;
    Move();
}

void Zombie::Move() { x -= speed; }

void Zombie::Bite(GameObject* target) {
    attackCounter++;
    if (attackCounter >= 30) {
        target->ReduceHP(10);
        attackCounter = 0;
    }
}