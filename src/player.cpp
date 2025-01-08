#include "player.hpp"
#include "globals.hpp"
#include "colors.hpp"

void Player::draw()
{
    tft.fillRect(x, y, 10, 10, GREEN); // Draw a green square representing the player
}

void Player::move(int direction)
{
    // 1 is right, -1 is left, 0 is no movement
    x += direction * 4;
    if (x < 0)
        x = 0;
    if (x > tft.width() - 10)
        x = tft.width() - 10;
}

bool Player::shoot()
{
    return digitalRead(JOYSTICK_BUTTON) == LOW; // Shoot when the button is pressed
}
