#include <Servo.h>
#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Ensure you have this library installed

// --- Pin Definitions  ---

// 1. DC Motor (L293D)
const int dcSpeedPin = 5; // D5 - PWM speed control 
const int dcDirPin1 = 2;  // D2 - Direction control 
const int dcDirPin2 = 3;  // D3 - Direction control 

// 2. Servo Motor
const int servoPin = 6;   // D6 - PWM position control 

// 3. Stepper Motor (ULN2003 with 28BYJ-48)
// Pins: D8, D9, D10, D11 
const int stepsPerRevolution = 2048; 
// Note: Sequence for 28BYJ-48 with standard library is often IN1-IN3-IN2-IN4
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11); 

// 4. Feedback & Inputs
const int buzzerPin = 13; // D13 - Active Buzzer [cite: 15, 24]
const int potDC = A0;     // Potentiometer for DC Motor 
const int potStepper = A1;// Potentiometer for Stepper Motor 
const int potServo = A2;  // Potentiometer for Servo Motor 

// LCD I2C (16x2) [cite: 51] - Standard address is usually 0x27 or 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo myServo;

void setup() {
  // Initialize Serial for ESP8266 communication (RX/TX) 
  // Standard baud rate for ESP-01 is usually 115200
  Serial.begin(115200);

  // DC Motor Setup
  pinMode(dcSpeedPin, OUTPUT);
  pinMode(dcDirPin1, OUTPUT);
  pinMode(dcDirPin2, OUTPUT);
  // Set initial direction to forward
  digitalWrite(dcDirPin1, HIGH);
  digitalWrite(dcDirPin2, LOW);

  // Servo Setup
  myServo.attach(servoPin);

  // Buzzer Setup
  pinMode(buzzerPin, OUTPUT);

  // LCD Setup
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Starting");

  // Startup sound feedback [cite: 24]
  tone(buzzerPin, 1000, 500); // 1000Hz for 500ms
  delay(1000);
  lcd.clear();
}

void loop() {
  // --- 1. DC Motor Control ---
  int dcVal = analogRead(potDC);
  int dcSpeed = map(dcVal, 0, 1023, 0, 255); // Map to PWM range
  analogWrite(dcSpeedPin, dcSpeed);

  // --- 2. Stepper Motor Control ---
  int stepVal = analogRead(potStepper);
  int stepSpeed = map(stepVal, 0, 1023, 0, 15); // Map to RPM (Max ~15 for 28BYJ-48)
  if (stepSpeed > 0) {
    myStepper.setSpeed(stepSpeed);
    // Step a small fraction to allow other code to run without blocking too long
    myStepper.step(stepsPerRevolution / 100); 
  }

  // --- 3. Servo Motor Control ---
  int servoVal = analogRead(potServo);
  int servoAngle = map(servoVal, 0, 1023, 0, 180); // Map to degrees
  myServo.write(servoAngle);

  // --- Update LCD ---
  lcd.setCursor(0, 0);
  lcd.print("DC: "); lcd.print(dcSpeed); lcd.print("  "); // Padded with spaces to clear old chars
  lcd.setCursor(0, 1);
  lcd.print("Srv: "); lcd.print(servoAngle); lcd.print(char(223)); lcd.print("  ");

  // --- Send data to ESP8266  ---
  // This prints a comma-separated string that your remote server/terminal can read
  Serial.print("DC_PWM:"); Serial.print(dcSpeed);
  Serial.print(",STEP_RPM:"); Serial.print(stepSpeed);
  Serial.print(",SRV_DEG:"); Serial.println(servoAngle);

  delay(50); // Small delay for system stability
}