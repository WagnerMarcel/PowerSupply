#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define analogIn  A1
#define inputVoltage A0

#define mVperAmp 186 
#define sensdiff 39

int readValue = 0; 

float sense = 0;
float vcc = 0; 
float voltage = 0; 
float ampere = 0; 

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
  readValue = analogRead(analogIn); 
  
  vcc = (float) 3.30 / analogRead(inputVoltage) * 1023.0;
  voltage = (float) readValue * vcc / 1023; 
  voltage = (float) voltage - (vcc/2);
  sense = (float) mVperAmp - ((5.00-vcc)*sensdiff); 
  ampere = (float)(voltage * sense)/1000; 

  
  lcd.clear();
  lcd.print("Volt: ");
  if(analogIn != 512){
    lcd.print("5V");
  }
  lcd.setCursor(0,1);
  lcd.print("Ampere: ");
  if(analogRead(analogIn) != 512){
    lcd.print(ampere);
  }
  lcd.print("A");
  
  Serial.print("Raw Value = " ); // shows pre-scaled value  
  Serial.print(readValue);  
  Serial.print("\t mV = "); // shows the voltage measured  
  Serial.print(voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point 
  Serial.print("\t Amps = "); // shows the voltage measured  
  Serial.print(ampere,3); // the '3' after voltage allows you to display 3 digits after decimal point
  Serial.print("\t Vcc = ");
  Serial.print(vcc);
  Serial.print("\t Sense = ");
  Serial.print(sense);
  Serial.println(" ");
  delay(2500); 
} 
