#include "Bullet.h"

Bullet::Bullet(int _x, int _y) : GameObject(_x, _y, 1), damage(20) {
    LoadImage(_T("res/bullet.png"), 15, 15);
}

void Bullet::Draw() {
    if (hasImage) {
        putimage(x - 7, y - 7, &img);
    }
    else {
        setfillcolor(YELLOW);
        solidcircle(x, y, 5);
    }
}

RECT Bullet::GetRect() {
    RECT r = { x - 5, y - 5, x + 5, y + 5 };
    return r;
}

void Bullet::Update() {
    x += 10;
    if (x > 900) hp = 0;
}

int Bullet::GetDamage() const { return damage; }