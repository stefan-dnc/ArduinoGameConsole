#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <Adafruit_ST7735.h>

extern Adafruit_ST7735 tft;

#define BUZZER 5
#define JOYSTICK_X A1
#define JOYSTICK_Y A2
#define JOYSTICK_BUTTON 3
#define BUTTON 4

extern int selectedItem;
extern const char *menuItems[];
extern const int menuCount;

#endif
