float sense = 0;
float vcc = 0;

float volt_calc_1 = 0;
float amp_1 = 0; 

float volt_calc_2 = 0;
float amp_2 = 0;

void measure() {
  vcc = (float) 3.30 / analogRead(inputVoltage) * 1023.0;
  sense = (float) mVperAmp - ((5.00-vcc)*sensdiff);

  volt_calc_1 = (float) analogRead(Sensor1) * vcc / 1023;
  volt_calc_1 = (float) volt_calc_1 - (vcc/2);
  amp_1 = (float)(volt_calc_1 * sense)/1000;

  volt_calc_2 = (float) analogRead(Sensor2) * vcc / 1023;
  volt_calc_2 = (float) volt_calc_2 - (vcc/2);
  amp_2 = (float)(volt_calc_2 * sense)/1000;
}
