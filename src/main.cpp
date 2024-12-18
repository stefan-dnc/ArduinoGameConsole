#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h> 
#include <SPI.h>

#define TFT_CS 10
#define TFT_RST 9
#define TFT_DC 8
#define TFT_LED A0
#define JOYSTICK_X A1
#define JOYSTICK_Y A2
#define JOYSTICK_BUTTON 3
#define BUTTON 4
#define BUZZER 5

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

#define BLACK ST7735_BLACK
#define RED 0xF00F
#define BLUE 0x07FF
#define CYAN 0x0FEF
#define YELLOW 0xFF0F
#define ORANGE 0xF80F
#define WHITE 0xFFFF
#define PURPLE 0x86FF
#define CYAN 0x07FF

void drawBootScreen();
void drawGrowingBorder();
void animateText(const char *text, int x, int y, uint16_t color);
void drawMainMenu();
void selectMenuItem(int selectedItem);

int selectedItem = 0; 
const char *menuItems[] = {"Start Game", "Settings", "Exit"};
const int menuCount = sizeof(menuItems) / sizeof(menuItems[0]);

int joystickButtonStatus = 0, lastJoyStickButtonStatus = 0; 
unsigned long lastDebounceTime = 0, debounceDelay = 50, joystickButtonStart = 0; 

int melody[] = {
    262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988, 1047}; 

void setup(void)
{
    pinMode(JOYSTICK_BUTTON, INPUT_PULLUP); 
    Serial.begin(9600);       
    tft.initR(INITR_144GREENTAB); 
    tft.fillScreen(BLACK); 

    pinMode(TFT_LED, OUTPUT); 
    analogWrite(TFT_LED, 128); 

    pinMode(BUTTON, INPUT_PULLUP); 
    pinMode(BUZZER, OUTPUT); 

    drawBootScreen();
    delay(2000); 

    drawMainMenu();
}

void loop()
{
    joystickButtonStatus = !digitalRead(JOYSTICK_BUTTON);

    if (joystickButtonStatus != lastJoyStickButtonStatus)
    {
        lastDebounceTime = millis();
        if (joystickButtonStatus)
            joystickButtonStart = millis();
    }

    if (joystickButtonStatus && (millis() - lastDebounceTime) > debounceDelay)
    {
        selectMenuItem(selectedItem);
    }
    
    lastJoyStickButtonStatus = joystickButtonStatus;

    int x = analogRead(JOYSTICK_X);
    int y = analogRead(JOYSTICK_Y);

    if(y < 256)
    {
        selectedItem = (selectedItem - 1) % menuCount;
        if(selectedItem < 0)
        {
            selectedItem = selectedItem + menuCount;
        }
        drawMainMenu();
        delay(200);
    }
    else if(y > 768)
    {
        selectedItem = (selectedItem + 1) % menuCount;
        drawMainMenu();
        delay(200);
    }
}

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

void selectMenuItem(int selectedIndex)
{
    switch (selectedIndex)
    {
    case 0:
        tft.fillScreen(BLACK);
        delay(1000);
        break;

    case 1:
        tft.fillScreen(BLACK);
        tft.setTextColor(WHITE);
        tft.setCursor(20, 50);
        tft.print("Opening Settings...");
        delay(1000);
        break;

    case 2:
        tft.fillScreen(BLACK);
        tft.setTextColor(WHITE);
        tft.setCursor(20, 50);
        tft.print("Exiting...");
        delay(1000);
        break;
    }
}