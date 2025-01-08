#include "enemy.hpp"
#include "globals.hpp"
#include "colors.hpp"

void Enemy::draw()
{
    tft.fillRect(x, y, 10, 10, RED); // Draw a red square representing the enemy
}

void Enemy::move()
{
    static int moveCounter = 0;
    moveCounter++;
    if (moveCounter % 5 == 0) // Move every 5 frames
    {
        x += direction * 1; // Slower speed
        if (x <= 0 || x >= tft.width() - 10)
            direction *= -1;
    }
}

bool Enemy::shoot()
{
    return random(0, 100) < 5; // 5% chance to shoot a bullet each frame
}
