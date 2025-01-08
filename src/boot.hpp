#ifndef BOOT_HPP
#define BOOT_HPP

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

void drawBootScreen();
void drawGrowingBorder();
void animateText(const char *text, int x, int y, uint16_t color);
void drawMainMenu();
void selectMenuItem(int selectedItem);

#endif
