/*
********************
* ATX Power Supply *
********************

What: Code for a desk power supply made from a ATX power supply
Who:  Marcel Wagner
When: Summer/Fall 2018
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Sensor Data
#define inputVoltage A0
#define Sensor1 A1
#define Sensor2 A2

// Adjustment for Sensor
#define mVperAmp 186
#define sensdiff 39

// Buttons for navigation the UI
#define Button_up 2
#define Button_down 3
#define Button_select 4
#define Button_back 5

uint8_t block[9]  = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa};

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  pinMode(Sensor1, INPUT);
  pinMode(Button_up, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(Button_select), button_select, RISING);
  attachInterrupt(digitalPinToInterrupt(Button_back), button_back, RISING);

  lcd.begin();
  lcd.backlight();

  lcd.createChar(0, block);

  Serial.begin(9600);
}

void loop() {
  measure();
  screen();
}
