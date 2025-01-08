#include "bullet.hpp"
#include "globals.hpp"
#include "colors.hpp"

// Default constructor
Bullet::Bullet() : x(0), y(0), isPlayerBullet(false), active(false) {}

// Constructor with parameters
Bullet::Bullet(int startX, int startY, bool playerBullet)
    : x(startX), y(startY), isPlayerBullet(playerBullet), active(true) {}

// Move the bullet
void Bullet::move()
{
    if (active)
    {
        y += isPlayerBullet ? -3 : 3; // Move up if player bullet, down if enemy bullet
        if (y < 0 || y > tft.height())
        {
            active = false; // Deactivate if off screen
        }
    }
}

// Draw the bullet
void Bullet::draw()
{
    if (active)
    {
        tft.fillRect(x, y, 2, 5, isPlayerBullet ? WHITE : YELLOW); // Player bullet white, enemy bullet yellow
    }
}

// Check if the bullet is off the screen
bool Bullet::isOffScreen()
{
    return !active;
}
