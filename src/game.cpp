#include "game.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include <Arduino.h>


extern Adafruit_ST7735 tft;

#define MAX_BULLETS 10
Bullet bullets[MAX_BULLETS];
int bulletCount = 0;
int waveNumber = 1;

// Function to read the joystick X-axis and return a direction (-1, 0, 1)
int getJoystickDirection()
{
    int x = analogRead(JOYSTICK_X);
    if (x < 400)
        return -1; // Left
    if (x > 600)
        return 1; // Right
    return 0;     // Neutral
}

void resetGameState(Player &player, Enemy enemies[], int numEnemies)
{
    // Reset bullets
    bulletCount = 0;
    // Reset player health
    player.health = 3;
    // Reset enemy positions and health for the next wave
    for (int i = 0; i < numEnemies; i++)
    {
        enemies[i] = Enemy(10 + i * 30, 10, waveNumber); // Change enemy health based on wave
    }
}

void showWaveNumber(int wave)
{
    tft.fillScreen(BLACK);
    tft.setTextColor(WHITE);
    tft.setCursor(30, 50);
    tft.print("Wave ");
    tft.print(wave);
    delay(2000); // Show the wave for 2 seconds
}

void handleBullets(Player &player, Enemy enemies[], int numEnemies)
{
    for (int i = 0; i < bulletCount; i++)
    {
        bullets[i].move();
        bullets[i].draw();

        if (bullets[i].isOffScreen())
        {
            bullets[i] = bullets[--bulletCount]; // Remove bullet by replacing it with the last bullet
            continue;
        }

        if (bullets[i].isPlayerBullet)
        {
            for (int j = 0; j < numEnemies; j++)
            {
                if (enemies[j].health > 0 && bullets[i].x > enemies[j].x && bullets[i].x < enemies[j].x + 10 &&
                    bullets[i].y > enemies[j].y && bullets[i].y < enemies[j].y + 10)
                {
                    enemies[j].health--;
                    bullets[i] = bullets[--bulletCount]; // Remove bullet
                    break;
                }
            }
        }
        else
        {
            if (bullets[i].x > player.x && bullets[i].x < player.x + 10 &&
                bullets[i].y > player.y && bullets[i].y < player.y + 10)
            {
                player.health--;
                bullets[i] = bullets[--bulletCount]; // Remove bullet
            }
        }
    }
}

void addBullet(int x, int y, bool isPlayerBullet)
{
    if (bulletCount < MAX_BULLETS)
    {
        bullets[bulletCount++] = Bullet(x, y, isPlayerBullet);
    }
}

void startGame()
{
    tft.fillScreen(BLACK);
    tft.setTextColor(WHITE);
    tft.setCursor(20, 50);
    tft.print("Starting Game...");
    delay(1000);

    Player player(tft.width() / 2 - 5, tft.height() - 15);

    const int numEnemies = 3;
    Enemy enemies[numEnemies] = {
        Enemy(10, 10, waveNumber),
        Enemy(40, 10, waveNumber),
        Enemy(70, 10, waveNumber)};

    while (true)
    {
        // Show wave number before starting each wave
        showWaveNumber(waveNumber);

        // Reset the game state for the new wave
        resetGameState(player, enemies, numEnemies);

        // Main game loop for the wave
        while (player.health > 0)
        {
            tft.fillScreen(BLACK);

            // Move and draw enemies
            for (int i = 0; i < numEnemies; i++)
            {
                if (enemies[i].health > 0) // Only draw and move alive enemies
                {
                    enemies[i].move();
                    enemies[i].draw();

                    if (enemies[i].shoot())
                    {
                        addBullet(enemies[i].x + 4, enemies[i].y + 10, false);
                    }
                }
            }

            // Move and draw player
            int direction = getJoystickDirection();
            player.move(direction);
            player.draw();

            // Check for bullet collisions
            if (player.shoot())
            {
                addBullet(player.x + 4, player.y - 5, true);
            }

            handleBullets(player, enemies, numEnemies);

            delay(50); // Delay to control game speed

            // If all enemies are killed, go to next wave
            bool allEnemiesDead = true;
            for (int i = 0; i < numEnemies; i++)
            {
                if (enemies[i].health > 0)
                {
                    allEnemiesDead = false;
                    break;
                }
            }

            if (allEnemiesDead)
            {
                waveNumber++; // Increase the wave number
                break;        // Go to the next wave
            }
        }

        // If the player has no health, show Game Over and restart
        if (player.health <= 0)
        {
            tft.fillScreen(BLACK);
            tft.setCursor(20, 50);
            tft.print("Game Over!\n");
            tft.setCursor(20, 70);
            tft.print("Waves survived: ");
            tft.print(waveNumber - 1); // Show the wave number before the player died
            delay(2000);               // Wait for 2 seconds before restarting
            waveNumber = 1;            // Reset wave number for the next game
            drawMainMenu();
            break;
        }
    }
}
