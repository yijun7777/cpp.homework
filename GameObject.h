#pragma once
#include <graphics.h>

class GameObject {
protected:
    int x, y, hp;
    IMAGE img;       // 图片对象
    bool hasImage;   // 图片是否加载成功

public:
    GameObject(int _x, int _y, int _hp);
    virtual ~GameObject() {}

    virtual void Draw() = 0;
    virtual void Update() = 0;
    virtual RECT GetRect();

    // 加载图片，成功返回 true
    bool LoadImage(LPCTSTR path, int w, int h);

    int GetX() const;
    int GetY() const;
    int GetHP() const;
    void ReduceHP(int damage);
    bool IsDead() const;
};