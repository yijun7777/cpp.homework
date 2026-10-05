#include "Plant.h"

Plant::Plant(int _x, int _y)
    : GameObject(_x, _y, 100), sunCost(50), attackTime(60), counter(0) {
    LoadImage(_T("res/plant.png"), 60, 60);
}

void Plant::Draw() {
    if (hasImage) {
        putimage(x, y, &img);
    }
    else {
        setfillcolor(GREEN);
        solidrectangle(x, y, x + 40, y + 40);
    }
}

void Plant::Update() {
    if (IsDead()) return;
    counter++;
    if (counter >= attackTime) counter = 0;
}

Bullet* Plant::Attack() {
    return new Bullet(x + 50, y + 25);
}

int Plant::GetSunCost() const { return sunCost; }