#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player
{
public:
    int x, y, health;

    Player(int startX, int startY)
        : x(startX), y(startY), health(3) {}

    void draw();
    void move(int direction);
    bool shoot();
};

#endif
