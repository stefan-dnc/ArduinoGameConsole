#ifndef ENEMY_HPP
#define ENEMY_HPP

class Enemy
{
public:
    int x, y, health;
    int direction; // 1 for right, -1 for left

    Enemy(int startX, int startY, int initialHealth)
        : x(startX), y(startY), health(initialHealth), direction(1) {}

    void move();
    void draw();
    bool shoot();
};

#endif
