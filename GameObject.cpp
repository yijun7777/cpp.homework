#include "GameObject.h"

GameObject::GameObject(int _x, int _y, int _hp)
    : x(_x), y(_y), hp(_hp), hasImage(false) {
}

RECT GameObject::GetRect() {
    RECT r = { x, y, x + 40, y + 40 };
    return r;
}

bool GameObject::LoadImage(LPCTSTR path, int w, int h) {
    loadimage(&img, path, w, h, true);
    hasImage = (img.getwidth() > 0);
    return hasImage;
}

int GameObject::GetX() const { return x; }
int GameObject::GetY() const { return y; }
int GameObject::GetHP() const { return hp; }
void GameObject::ReduceHP(int damage) { hp -= damage; }
bool GameObject::IsDead() const { return hp <= 0; }