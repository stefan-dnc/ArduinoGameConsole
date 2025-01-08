#include "settings.hpp"
#include "colors.hpp"
#include "globals.hpp"
#include "config.hpp"
#include <Arduino.h>

extern Adafruit_ST7735 tft;

int brightnessLevel = 128;    // Default brightness level

void drawSettingsMenu()
{
    tft.fillScreen(BLACK);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);

    tft.setCursor(20, 30);
    tft.print("Settings:");

    // Brightness control
    tft.setCursor(20, 90);
    tft.print("Brightness: ");
    tft.print(round(map(brightnessLevel,128,255,0,10)));
}

void setBrightness()
{
    analogWrite(TFT_LED, brightnessLevel);

    tft.fillScreen(BLACK);
    tft.setCursor(20, 50);
    tft.print("Settings applied!");
    delay(1000);
    drawSettingsMenu();
}

void adjustBrightness(int value)
{
    brightnessLevel = constrain(brightnessLevel + value, 128, 255);
    drawSettingsMenu();
}
