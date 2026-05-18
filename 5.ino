#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

const int sw = 18;
const int led1 = 19;

void setup() {
  lcd.init();  
  lcd.backlight();
  lcd.print("Hello, world!");
  pinMode(sw, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
}
void loop() {
  int adc32 = analogRead(32);
  float volt32 = (adc32/4095.0)*3.3;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ADC:");
  lcd.setCursor(4,0);
  lcd.print(adc32);
  lcd.setCursor (10,0);
  lcd.print("Volt:");
  lcd.setCursor(15,0);
  lcd.print(volt32);
  lcd.setCursor(0,1);
  lcd.print("SW:");
  lcd.setCursor(3, 1);
  if(digitalRead(sw)){
    lcd.print("OFF");
    digitalWrite(led1, LOW);
  }
  else{
    lcd.print("ON");
    if(volt32 >= 2.5){
      digitalWrite(led1, HIGH);
    }
    else if(volt32 < 2.5){
      digitalWrite(led1, LOW);
    }
  }
  lcd.setCursor(10,1);
  lcd.print("LED: ");
  lcd.setCursor(14,1);
  if(digitalRead(led1)){
    lcd.print("ON");
  }
  else{
    lcd.print("OFF");
  }
  delay(500);

}