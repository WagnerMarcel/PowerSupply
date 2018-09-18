/*
Select button to enter changing setup.
All Channels start blinking.
Switch with the up / down button through the different voltage and ampere channels
CH1 Voltage -> CH1 Ampere (maximum rating) -> CH2 Voltage -> CH2 Ampere
Select the desired one with the select button.
Selected one blinks.
Set Voltage (CH1 3.3V/5V and CH2 5V/12V)
Set Ampere (default 1A max 3A);
*/

float volt_1;
float volt_2;

int time_dif_old = 0;
int selected = 0; // Menu point selection (0 = All; 1 = CH1V; 2 = CH2A; 3 = CH2V; 4 = CH2A)
boolean toggle = false;
boolean chng = false;
/*
****************
CH1:1.1VCH2:2.2V
    1.1A    2.2A
****************
*/
void screen() {


}

void voltage_1(float volt){
  lcd.setCursor(0,0);
  lcd.print("CH1:");
  lcd.setCursor(4,0);
    if(volt != 0){
    lcd.print(round(volt*10)/10);
  }
  lcd.setCursor(7, 0);
  lcd.print("V");
}

void ampere_1(float amp){
  lcd.setCursor(4,1);
  if(amp != 0){
    lcd.print(round(amp*10)/10);
  }
  lcd.setCursor(7, 1);
  lcd.print("A");
}

void voltage_2(float volt){
  lcd.setCursor(8,0);
  lcd.print("CH2:");
  lcd.setCursor(12,0);
    if(volt != 0){
    lcd.print(round(volt*10)/10);
  }
  lcd.setCursor(15, 0);
  lcd.print("V");
}

void ampere_2(float amp){
  lcd.setCursor(12,1);
  if(amp != 0){
    lcd.print(round(amp*10)/10);
  }
  lcd.setCursor(15, 1);
  lcd.print("A");
}

void change(){
  while(chng){
    int time_dif = millis()- time_dif_old;
    if(time_dif > 1000){
      toggle != toggle;
      time_dif_old += time_dif;
      if(toggle){
        switch(selected){
          case 0: voltage_1(volt_1);
                  ampere_1(amp_1);
                  voltage_2(volt_2);
                  ampere_2(amp_2);
                  break;
          case 1: voltage_1(volt_1);
                  break;
          case 2: ampere_1(amp_1);
                  break;
          case 3: voltage_2(volt_2);
                  break;
          case 4: ampere_2(amp_2);
                  break;
          default:break;
        }
      }else{
        switch(selected){
          case 0: voltage_1(0);
                  ampere_1(0);
                  voltage_2(0);
                  ampere_2(0);
                  break;
          case 1: voltage_1(0);
                  break;
          case 2: ampere_1(0);
                  break;
          case 3: voltage_2(0);
                  break;
          case 4: ampere_2(0);
                  break;
          default:break;
        }
      }
    }
  }
}
