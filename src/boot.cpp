#include "boot.hpp"
#include "colors.hpp"
#include "globals.hpp"
#include "config.hpp"
#include "game.hpp"
#include <Arduino.h>

extern Adafruit_ST7735 tft;

int melody[] = {
    262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988, 1047};

void drawBootScreen()
{
    tft.fillScreen(BLACK);
    drawGrowingBorder();

    for (int thisNote = 0; thisNote < 15; thisNote++)
    {
        tone(BUZZER, melody[thisNote], 20);
        int pauseBetweenNotes = 20 * 1.30;
        delay(pauseBetweenNotes);
        noTone(BUZZER);
    }

    animateText("Ardu", (tft.width() - (4 * 12)) / 2, 40, WHITE);
    delay(300);
    animateText("Station", (tft.width() - (7 * 12)) / 2, 70, RED);
}

void drawGrowingBorder()
{
    int delayTime = 100;

    tft.drawRect(0, 0, tft.width(), tft.height(), CYAN);
    tone(BUZZER, 262, 200);
    delay(delayTime);

    tft.drawRect(2, 2, tft.width() - 4, tft.height() - 4, BLUE);
    tone(BUZZER, 294, 200);
    delay(delayTime);

    tft.drawRect(4, 4, tft.width() - 8, tft.height() - 8, PURPLE);
    tone(BUZZER, 330, 200);
    delay(delayTime);

    tft.drawRect(6, 6, tft.width() - 12, tft.height() - 12, RED);
    tone(BUZZER, 349, 200);
    delay(delayTime);

    tft.drawRect(8, 8, tft.width() - 16, tft.height() - 16, YELLOW);
    tone(BUZZER, 392, 200);
    delay(delayTime);

    tft.drawRect(10, 10, tft.width() - 20, tft.height() - 20, ORANGE);
    tone(BUZZER, 440, 200);
    delay(delayTime);

    tft.fillRect(12, 12, tft.width() - 24, tft.height() - 24, BLACK);
    noTone(BUZZER);
}

void animateText(const char *text, int x, int y, uint16_t color)
{
    tft.setTextSize(2);
    tft.setTextColor(color);
    int charWidth = 12;

    for (int i = 0; text[i] != '\0'; i++)
    {
        tft.setCursor(x + (i * charWidth), y);
        tft.print(text[i]);
        delay(150);
    }
}

void drawMainMenu()
{
    tft.fillScreen(BLACK);

    tft.setTextSize(1);
    tft.setTextColor(WHITE);

    for (int i = 0; i < menuCount; i++)
    {
        if (i == selectedItem)
        {
            tft.setTextColor(YELLOW);
        }
        else
        {
            tft.setTextColor(WHITE);
        }

        tft.setCursor(20, 30 + (i * 20));
        tft.print(menuItems[i]);
    }
}