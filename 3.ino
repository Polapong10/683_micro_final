unsigned long Htime, Ltime, Ttime;

void setup() {
  Serial.begin(115200);
  analogReadResolution(10);
  ledcAttachChannel(18,5000,10,1);
  pinMode(27, INPUT);

}

void loop() {
  int adcVal33 = analogRead(33);
  float volt33 = (adcVal33/1023.0)*3.3;
  float duty33 = (adcVal33/1023.0) * 100.0;
  Serial.println("ADC33 = "+String(adcVal33)+" | Voltage = "+String(volt33)+" | Duty = "+String(duty33));
  ledcWriteChannel(1,adcVal33);

  Htime = pulseIn(27,HIGH,3000000L);
  delay(10);
  Ltime = pulseIn(27,LOW,300000L);

  Ttime = Htime+Ltime;
  float frq = 1000000.0/Ttime;
  float duty = ((float)Htime/Ttime)*100.0;

  Serial.println("Htime = "+String(Htime)+" | Ltime = "+String(Ltime)+" | Freq = "+String(frq)+" | Duty% = "+String(duty));

  delay(100);

}
