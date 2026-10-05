#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
private:
    int damage;

public:
    Bullet(int _x, int _y);

    void Draw() override;
    void Update() override;
    RECT GetRect() override;

    int GetDamage() const;
};