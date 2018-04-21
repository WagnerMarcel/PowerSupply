const int analogIn = A0; 
int mVperAmp = 185; 
int RawValue= 0; 
int ACSoffset = 2500;  
double Voltage = 0; 
double Amps = 0; 
 
void setup() { 
  // put your setup code here, to run once: 
  pinMode(analogIn, INPUT); 
  Serial.begin(9600); 
} 
 
void loop() { 
  // put your main code here, to run repeatedly: 
   RawValue = analogRead(analogIn); 
   Voltage = (RawValue / 1024.0) * 5000; // Gets you mV 
   Amps = ((Voltage - ACSoffset) / mVperAmp); 
  
  
   Serial.print("Raw Value = " ); // shows pre-scaled value  
   Serial.print(RawValue);  
   Serial.print("\t mV = "); // shows the voltage measured  
   Serial.print(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point 
   Serial.print("\t Amps = "); // shows the voltage measured  
   Serial.println(Amps,3); // the '3' after voltage allows you to display 3 digits after decimal point 
   delay(2500); 
} 
