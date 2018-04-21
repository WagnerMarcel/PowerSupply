#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int analogIn = A0; 
int mVperAmp = 185; 
int RawValue= 0; 
int ACSoffset = 2500;  
double Voltage = 0; 
double Amps = 0; 

uint8_t block[9]  = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa};

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() { 
  // put your setup code here, to run once:
  pinMode(analogIn, INPUT); 

  lcd.begin();
  lcd.backlight();

  lcd.createChar(0, block);
  
  Serial.begin(9600); 
} 
 
void loop() { 
  // put your main code here, to run repeatedly: 
  RawValue = analogRead(analogIn); 
  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV 
  Amps = ((Voltage - ACSoffset) / mVperAmp); 
  lcd.clear();
  lcd.print("Volt: ");
  if(analogIn != 512){
    lcd.print("5V");
  }
  lcd.setCursor(0,1);
  lcd.print("Ampere: ");
  if(analogRead(analogIn) != 512){
    lcd.print(Amps);
  }
  lcd.print("A");
  
  Serial.print("Raw Value = " ); // shows pre-scaled value  
  Serial.print(RawValue);  
  Serial.print("\t mV = "); // shows the voltage measured  
  Serial.print(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point 
  Serial.print("\t Amps = "); // shows the voltage measured  
  Serial.println(Amps,3); // the '3' after voltage allows you to display 3 digits after decimal point 
  delay(2500); 
} 
