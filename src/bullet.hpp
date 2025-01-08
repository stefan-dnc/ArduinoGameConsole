#ifndef BULLET_HPP
#define BULLET_HPP

class Bullet
{
public:
    int x, y;
    bool isPlayerBullet;
    bool active;

    // Default constructor
    Bullet();

    // Constructor with parameters
    Bullet(int startX, int startY, bool playerBullet);

    void move();
    void draw();
    bool isOffScreen();
};

#endif
