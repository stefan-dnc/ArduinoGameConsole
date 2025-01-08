# Arduino Game Console

## Table of Contents
[1. Introduction](#introduction)\
[2. Overview](#overview)\
[3. Hardware Design](#hardware-design)\
[4. Software Design](#software-design)\
[5. Setup](#setup)\
[6. Conclusions](#conclusions)\
[7. Resources](#resources)

## Introduction

This project focuses on developing a Game Console designed to deliver an engaging gaming experience through a custom-built game inspired by Chicken Invaders. The console integrates an LCD display, a joystick for directional input, a push button, and a buzzer for sound feedback. The system offers a complete standalone experience by using a battery pack.

At the core of this project is the integration of an ATMega328P microcontroller with peripherals to handle game logic, render visuals, and process user inputs in real-time. This project includes principles of embedded systems like SPI, analog-to-digital conversion (ADC), and timers to efficiently manage input, display updates, and game logic.

![Working project](media/circuit_photo.png)

## YouTube Video
[![YouTube Video](https://img.youtube.com/vi/MEEA9Vy9UWc/hqdefault.jpg)](https://www.youtube.com/watch?v=MEEA9Vy9UWc)

### LCD Close-Up View

The image below showcases the **ST7735 LCD Display** in operation, rendering the boot screen via SPI communication. 
![LCD close-up](media/LCD_close-up.png)

## Overview
### Features
- Interactive Gameplay
    - A dynamic, challenging game inspired by Chicken Invaders.
    - Real-time updates and responses based on user input.
    - Enemy wave system to track player performance.
- Main Menu
    - Start new game.
    - Change display brightness.
    - View details about the project.
- Custom Hardware Integration
    - Joystick: For smooth bidirectional input and a built-in switch for special actions.
    - Push Button: Handles secondary actions.
    - LCD Display: Renders game visuals and menus.
    - Buzzer: Provides audio feedback for interactions.
- Portable Design
    - Powered by a 6V battery pack with an on/off switch.

### Block Diagram

![Draw.io](media/block_diagram.png)

## Hardware Design

### Components

| **Component**                  | **Quantity** | **Description**                          | **Source**               | **Datasheet**                                                                                   |
|--------------------------------|:------------:|------------------------------------------|--------------------------|-----------------------------------------------------------------------------------------------|
| ATMega328P Microcontroller     |      1       | Core microcontroller for the console      | University Robotics Lab  | [ATMega328P Datasheet](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/Atmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf) |
| 6V Battery Pack with Switch    |      1       | Provides portable power                   | University Robotics Lab  | N/A                                                                                           |
| ST7735 LCD Display             |      1       | Renders visuals and game information      | University Robotics Lab  | [ST7735 LCD Datasheet](http://www.lcdwiki.com/res/MSP1443/1.44inch_SPI_Module_MSP1443_User_Manual_EN.pdf) |
| Analog Joystick with Switch    |      1       | Directional input + button functionality  | University Robotics Lab  | [Joystick Datasheet](https://naylampmechatronics.com/img/cms/Datasheets/000036%20-%20datasheet%20KY-023-Joy-IT.pdf) |
| Push Button (with 1k Resistor) |      1       | Action button input                      | University Robotics Lab  | N/A                                                                                           |
| 1kΩ Resistor                   |      1       | Limits current for the push button        | University Robotics Lab  | N/A                                                                                           |
| Buzzer                         |      1       | Outputs sound feedback                    | University Robotics Lab  | [Buzzer Datasheet](https://www.farnell.com/datasheets/1738927.pdf)                             |
| 100Ω Resistor                  |      1       | Limits current for the buzzer             | University Robotics Lab  | N/A                                                                                           |
| Breadboard                     |      1       | Circuit prototyping platform              | University Robotics Lab  | N/A                                                                                           |
| Wires                          |      26      | Various connections and support           | University Robotics Lab  | N/A                                                                                           |

---

### Wiring Overview

The **ST7735 LCD** and **joystick** are the primary input/output peripherals. The components are wired as follows:

- **Joystick**:  
  - `VCC` → 5V  
  - `GND` → GND  
  - `VRx` → A1 (Analog X-Axis input)  
  - `VRy` → A2 (Analog Y-Axis input)  
  - `SW` → Pin 3 (Digital button input)  

- **ST7735 LCD**:  
  - `VCC` → 3.3V  
  - `GND` → GND    
  - `CS` → Pin 10  
  - `RESET` → Pin 9  
  - `A0` → Pin 8 
  - `SDA` → Pin 11
  - `SCK` → Pin 13  
  - `LED` → Analog Pin A0

- **Push Button**:  
  - One side → Pin 4 (Digital input)  
  - Other side → GND through **1kΩ resistor**.  

- **Buzzer**:  
  - Positive terminal → Pin 5 (PWM Output through 100Ω resistor).  
  - Negative terminal → GND.  

- **6V Battery Pack**:  
  - `VCC` → Vin  
  - `GND` → GND  

### Electrical scheme
![Wokwi](media/electrical_scheme.png)

## Software Design

### IDE and Libraries
- **IDE**: Visual Studio Code + PlatformIO  
- **Libraries**:  
  - `Adafruit GFX` (for ST7735 LCD graphics)  
  - `Adafruit ST7735` (to interface with LCD)
  - `SPI` (used for communication with the ST7735 LCD)

### Key Features and Functionalities 
#### Object-Oriented Programming (OOP)
Each game element (Player, Bullet, Enemy) has its own class, containing attributes like position, state, and behavior.
Scalable Difficulty

#### The game dynamically adjusts its difficulty based on the player's progress. Key aspects include:
- Enemy Speed: Enemies move faster and shoot more frequently as the player scores higher.
- Bullet Frequency: Both player and enemy bullets increase in frequency, intensifying the gameplay.

### Principal Functions
- void Bullet::move(): Updates bullet position, checks boundaries, and deactivates bullets off-screen.
- void Bullet::draw(): Renders bullets on the LCD using their current state and position.
- void Player::move(int direction): Handles player movement based on joystick input, ensuring boundaries are respected.
- void Player::shoot(): Returns true when the joystick button is pressed, initiating bullet firing.
- void Enemy::move(): Controls enemy movement with periodic direction changes and boundary checks.
- bool Enemy::shoot(): Determines enemy shooting probability per frame, adding randomness to the gameplay.

### Advanced Techniques

#### PWM for LCD Brightness
**PWM (Pulse Width Modulation)** is utilized via the analogWrite() function to adjust the LCD brightness in settings.

#### Button Debouncing Using Timers
The push button utilizes a software **debouncing** technique implemented through millis(). This approach tracks the time elapsed since the last button press, ignoring spurious signals and ensuring reliable input detection. The debounce logic improves game responsiveness and reduces input errors.

#### SPI Communication for LCD
**SPI (Serial Peripheral Interface)** ensures high-speed communication between the microcontroller and the ST7735 LCD. The game uses this protocol to efficiently update the screen with minimal latency. Commands and data are sent through dedicated MOSI and SCK lines, while control signals (CS, RESET, A0) manage the LCD's state and operations.

## Setup

1. **Hardware Assembly**:  
   - Follow the wiring diagram to connect all components:  
     - Connect the **LCD** to digital pins for SPI communication.  
     - Wire the **joystick** and **push button** to their respective pins.  
     - Attach the **buzzer** to Pin 5 with a 100Ω resistor.  
     - Power the system via the **6V battery pack** connected to `Vin` and `GND`.

2. **Software Installation**:  
   - Install **Visual Studio Code** and **PlatformIO**.  
   - Clone the repository and open it in PlatformIO.  
   - Install required libraries through the PlatformIO Library Manager.  

3. **Upload Code**:  
   - Compile and upload the code to the **ATMega328P**.  

4. **Run the Console**:  
   - Use the on/off switch to power the system.  
   - Control gameplay using the joystick and button inputs.  

## Additional Features or Future Improvements
- Dynamic scalable enemies: advanced enemies, dynamically growing number of enemies
- High score persistence: saving user data locally
- Customization options: more settings to adapt to user preference

## Conclusions
The use of Object-Oriented Programming (OOP) principles was very useful in designing this project. By encapsulating game elements like the player, bullets, and enemies into modular classes, the whole project remains scalable. This structure supports the easy addition of new features in the future like derived classes for special enemies and allows for the game difficulty to scale dynamically, providing a good gaming experience.

In conclusion, the Arduino Game Console (ArduStation) presents how well hardware and software can work together to deliver a robust and enjoyable gaming experience. The project was created by using both embedded systems and OOP principles and this approach makes it a valuable project for learning and demonstration purposes. 

## Resources

### Hardware Resources
- [ATMega328P Datasheet](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf)  
- [ST7735 LCD Datasheet](http://www.lcdwiki.com/res/MSP1443/1.44inch_SPI_Module_MSP1443_User_Manual_EN.pdf)  
- [Joystick Datasheet](https://naylampmechatronics.com/img/cms/Datasheets/000036%20-%20datasheet%20KY-023-Joy-IT.pdf)  
- [Buzzer Datasheet](https://www.farnell.com/datasheets/1738927.pdf)

### Software Resources
- [PlatformIO](https://platformio.org)  
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)  
- [Adafruit ST7735 Library](https://github.com/adafruit/Adafruit-ST7735-Library)
