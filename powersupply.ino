#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define inputVoltage A0
#define Sensor1 A1
#define Sensor2 A2
#define Sensor3 A3
#define Button 2

#define mVperAmp 186 
#define sensdiff 39

int screen = 0;

float display_v = 0;
float display_a = 0;

float sense = 0;
float vcc = 0; 

float voltage_1 = 0; 
float ampere_1 = 0; 

float voltage_2 = 0; 
float ampere_2 = 0;

float voltage_3 = 0; 
float ampere_3 = 0;

uint8_t block[9]  = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa};

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() { 
  // put your setup code here, to run once:
  pinMode(Sensor1, INPUT);
  pinMode(Button, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(Button), change, RISING);

  lcd.begin();
  lcd.backlight();

  lcd.createChar(0, block);
  
  Serial.begin(9600); 
} 
 
void loop() { 
  // put your main code here, to run repeatedly: 
  
  vcc = (float) 3.30 / analogRead(inputVoltage) * 1023.0;
  sense = (float) mVperAmp - ((5.00-vcc)*sensdiff); 
  
  voltage_1 = (float) analogRead(Sensor1) * vcc / 1023; 
  voltage_1 = (float) voltage_1 - (vcc/2);
  ampere_1 = (float)(voltage_1 * sense)/1000; 

  voltage_2 = (float) analogRead(Sensor2) * vcc / 1023; 
  voltage_2 = (float) voltage_2 - (vcc/2);
  ampere_2 = (float)(voltage_2 * sense)/1000; 

  voltage_3 = (float) analogRead(Sensor3) * vcc / 1023; 
  voltage_3 = (float) voltage_3 - (vcc/2);
  ampere_3 = (float)(voltage_3 * sense)/1000; 


  switch(screen){
    case 0: display_v = 5.00;
            display_a = ampere_1;
            break;
    case 1: display_v = 3.30;
            display_a = ampere_2;
            break;
    case 2: display_v = 12.00;
            display_a = ampere_3;
            break;
    default: break;
    
  }
  
  lcd.clear();
  lcd.print("Volt:");
  lcd.setCursor(8,0);
  lcd.print(display_v);
  lcd.setCursor(13, 0);
  lcd.print("V");
  lcd.setCursor(0,1);
  lcd.print("Ampere:");
  lcd.setCursor(8,1);
  lcd.print(display_a);
  lcd.setCursor(13, 1);
  lcd.print("A");

  Serial.print("\t mV 1 = "); // shows the voltage_1 measured  
  Serial.print(voltage_1,3); // the '3' after voltage_1 allows you to display 3 digits after decimal point 
  Serial.print("\t Amps 1 = "); // shows the voltage_1 measured  
  Serial.print(ampere_1,3); // the '3' after voltage_1 allows you to display 3 digits after decimal point
  Serial.print("\t mV 2 = "); // shows the voltage_1 measured  
  Serial.print(voltage_2,3); // the '3' after voltage_1 allows you to display 3 digits after decimal point 
  Serial.print("\t Amps 2 = "); // shows the voltage_1 measured  
  Serial.print(ampere_2,3); // the '3' after voltage_1 allows you to display 3 digits after decimal point
  Serial.print("\t mV 3 = "); // shows the voltage_1 measured  
  Serial.print(voltage_3,3); // the '3' after voltage_1 allows you to display 3 digits after decimal point 
  Serial.print("\t Amps 3 = "); // shows the voltage_1 measured  
  Serial.print(ampere_3,3); // the '3' after voltage_1 allows you to display 3 digits after decimal point
  Serial.print("\t Vcc = ");
  Serial.print(vcc);
  Serial.print("\t Sense = ");
  Serial.print(sense);
  Serial.println(" ");
  delay(2500); 
} 

void change(){
  detachInterrupt(Button);
  screen++;
  if(screen > 2){
    screen = 0;
  }
  attachInterrupt(digitalPinToInterrupt(Button), change, RISING);
}

