# Wi-Fi Enabled Triple Motor Control System
> **An integrated Arduino-based platform for simultaneous control of DC, Stepper, and Servo motors with remote Wi-Fi monitoring.**

## 📌 Overview
This project features a modular control system designed to manage three distinct types of actuators simultaneously. [cite_start]It utilizes an **Arduino Nano** as the central logic unit and an **ESP8266** module to provide IoT capabilities, allowing for remote status tracking of motor parameters.

## 🚀 Key Features
* [cite_start]**Triple-Motor Synchrony**: Independent and simultaneous control of a DC Motor, Step Motor (28BYJ-48), and Servo Motor[cite: 458].
* **Hybrid Driver Architecture**: 
    * [cite_start]**L293D**: Bi-directional speed control for the DC motor[cite: 466].
    * [cite_start]**ULN2003**: Precision 4-phase driving for the Stepper motor[cite: 468].
* [cite_start]**Remote Monitoring**: Integrated ESP8266 (Wi-Fi) for transmitting real-time speed and position data to a remote terminal[cite: 460].
* [cite_start]**Precision Analog Interface**: Three dedicated potentiometers for real-time manual adjustment of motor velocity and angular position[cite: 460].
* [cite_start]**Advanced Power Management**: Multi-stage regulation (12V → 5V Buck via LM2596; 5V → 3.3V LDO via AMS1117) to ensure logic stability and high-current motor efficiency [cite: 473-477].

## 🛠️ Tech Stack
* **Microcontroller**: Arduino Nano.
* **IoT/Comms**: ESP8266 (Wi-Fi).
* **Drivers**: L293D (DC) & ULN2003A (Stepper).
* **Design Tools**: Proteus 8 Professional (Simulation & PCB Design), Arduino IDE.

## 📐 Hardware Design (PCB)
The system features a custom-designed **100mm x 100mm single-layer PCB**, optimized for home-based production. [cite_start]It utilizes a strategic jumper-wire approach to manage complex signal routing while maintaining a low-cost manufacturing profile .

## 📊 Pin Mapping
| Component | Function | Arduino Pin |
| :--- | :--- | :--- |
| DC Motor | PWM Speed / Direction | [cite_start]D5 / D2, D3 [cite: 462, 467] |
| Servo Motor | Position (PWM) | [cite_start]D6 [cite: 462] |
| Step Motor | 4-Phase Control | [cite_start]D8, D9, D10, D11 [cite: 462] |
| Inputs | Potentiometers | [cite_start]A0, A1, A2 [cite: 462] |
| Feedback | Buzzer / Status | [cite_start]D13 / I2C LCD  |

---
*Project developed for the Microcontroller Design course, January 2026.*