#include <Preferences.h>

#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

Preferences mymem;

String st_id;
float weight;
int height;

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* CS=*/ 5, /* reset=*/ 22); // ESP32


void setup() {
  Serial.begin(115200);
  u8g2.begin();

  Serial.println("Please enter Student ID: ");
  while(Serial.available()==0);
  st_id = Serial.readString();

  Serial.println("ID: "+st_id);
  mymem.begin(st_id.c_str(),false);

  while(true){
    Serial.println("Please enter y, n or x: ");
    while(Serial.available()==0);
    char cmd = Serial.read();
    if(cmd == 'x'){
      weight = mymem.getFloat("weight",0);
      height = mymem.getInt("height",0);
      Serial.println("Weight = "+String(weight));
      Serial.println("Height = "+String(height));
      Serial.println("");
    }
    else if(cmd == 'y'){
      Serial.println("Please enter student weight: ");
      while(Serial.available()==0);
      weight = Serial.readString().toFloat();
      Serial.println("Please enter student height: ");
      while(Serial.available()==0);
      height = Serial.readString().toInt();
      mymem.putFloat("weight", weight);
      mymem.putInt("height",height);
      Serial.println("Saving... Done");
    }
    else if(cmd == 'n'){
      weight = mymem.getFloat("weight",0);
      height = mymem.getInt("height",0);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_boutique_bitmap_9x9_t_gb2312a);
      u8g2.drawStr(32,15,("ID: "+st_id).c_str());
      u8g2.drawStr(32,35,("Weight: "+String(weight)).c_str());
      u8g2.drawStr(32,55,("Height: "+String(height)).c_str());
      u8g2.sendBuffer();
      break;
    }
  }

}

void loop() {

}
