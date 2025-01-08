#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#include "boot.hpp"
#include "game.hpp"
#include "colors.hpp"
#include "globals.hpp"
#include "config.hpp"
#include "settings.hpp"

// Initialize the LCD display with the necessary pins
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Main menu variables
int selectedItem = 0;
const char *menuItems[] = {"Start Game", "Settings", "About"};
const int menuCount = sizeof(menuItems) / sizeof(menuItems[0]);

// Joystick and button debounce variables
int joystickButtonStatus = 0, lastJoyStickButtonStatus = 0;
unsigned long lastDebounceTime = 0, debounceDelay = 50, joystickButtonStart = 0;
int buttonStatus = 0, lastButtonStatus = 0;
unsigned long buttonLastDebounceTime = 0, buttonDebounceDelay = 50, buttonStart = 0;

// State bools for menu navigation
bool menuSelected = false, settingsSelected = false;

void setup()
{
    // Setup pin modes for joystick, button, buzzer, and LCD backlight
    pinMode(JOYSTICK_BUTTON, INPUT_PULLUP);
    Serial.begin(9600);
    tft.initR(INITR_144GREENTAB);
    tft.fillScreen(BLACK);

    // Set the LCD backlight brightnes
    pinMode(TFT_LED, OUTPUT);
    analogWrite(TFT_LED, 128);

    // Initialize additional input and output components
    pinMode(BUTTON, INPUT_PULLUP);
    pinMode(BUZZER, OUTPUT);

    drawBootScreen();
    delay(2000);

    drawMainMenu();
}

void loop()
{
    // Read joystick button status and handle debouncing
    joystickButtonStatus = !digitalRead(JOYSTICK_BUTTON);

    if (joystickButtonStatus != lastJoyStickButtonStatus)
    {
        lastDebounceTime = millis();
        if (joystickButtonStatus)
            joystickButtonStart = millis();
    }

    // Handle menu selection if button press is stable
    if (joystickButtonStatus && (millis() - lastDebounceTime) > debounceDelay)
    {
        selectMenuItem(selectedItem);
    }

    lastJoyStickButtonStatus = joystickButtonStatus;

    // Joystick Y-axis handling for menu navigation
    int y = analogRead(JOYSTICK_Y);

    if (y < 256)
    {
        selectedItem = (selectedItem - 1 + menuCount) % menuCount;
        drawMainMenu();
        delay(400);
    }
    else if (y > 768)
    {
        selectedItem = (selectedItem + 1) % menuCount;
        drawMainMenu();
        delay(400);
    }
}

void selectMenuItem(int selectedIndex)
{
    switch (selectedIndex)
    {
    case 0:
        tft.fillScreen(BLACK);
        startGame();
        break;

    case 1:
        tft.fillScreen(BLACK);
        drawSettingsMenu();
        settingsSelected = false;
        while (!settingsSelected)
        {
            joystickButtonStatus = !digitalRead(JOYSTICK_BUTTON);

            if (joystickButtonStatus && (millis() - lastDebounceTime) > debounceDelay)
            {
                lastDebounceTime = millis();
                settingsSelected = true;
                drawMainMenu();
                delay(400);
            }

            buttonStatus = !digitalRead(BUTTON);

            if (buttonStatus && (millis() - buttonLastDebounceTime) > buttonDebounceDelay)
            {
                setBrightness();
                delay(200);
            }

            // Adjust brightness using joystick Y-axis
            if (analogRead(JOYSTICK_Y) < 256)
            {
                adjustBrightness(10);
                delay(200);
            }
            else if (analogRead(JOYSTICK_Y) > 768)
            {
                adjustBrightness(-10);
                delay(200);
            }
        }
        break;

    case 2:
        tft.fillScreen(BLACK);
        tft.setTextColor(WHITE);
        tft.setCursor(20, 50);
        tft.print("Ardu Station 2025\n");
        tft.setCursor(20, 70);
        tft.print("Version 1.0\n");
        delay(4000);
        drawMainMenu();
        break;
    }
}
