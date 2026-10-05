#pragma once
#include "GameObject.h"

class Zombie : public GameObject {
private:
    int speed;
    int attackCounter;

public:
    Zombie(int _x, int _y);

    void Draw() override;
    void Update() override;

    void Move();
    void Bite(GameObject* target);
};