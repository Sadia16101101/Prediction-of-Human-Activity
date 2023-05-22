 /*
  Memory card Module:
     MOSI - pin 11
     MISO - pin 12
     CLK  - pin 13
     CS   - pin 4

  Time Module:
    SCL - A5
    SDA - A4
    VCC - 5V
    GND - GND

  Gyro Module:
    SCL - A5
    SDA - A4
    VCC - 5V
    GND - GND
*/
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 accelgyro;

RTC_DS1307 RTC;

int16_t ax, ay, az;
int16_t gx, gy, gz;


int CS_PIN = 4;

File dataFile;

void setup() {
  Wire.begin();
  RTC.begin();
  Serial.begin(9600);
  accelgyro.initialize();
  
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  if (SD.begin(CS_PIN)){Serial.println("SD card Module success");}
  else{Serial.println("SD card module Failure");}
}

void loop() {
  DateTime now = RTC.now(); 
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  String str1 = String(now.day())+'/'+String(now.month())+'/'+String(now.year())+' '+String(now.hour())+':'+String(now.minute())+':'+String(now.second());
  String str2 = "ax: "+String(ax)+"\t"+"ay: "+String(ay)+"\t"+"az: "+String(az)+"\t"+"gx: "+String(gx)+"\t"+"gy: "+String(gy)+"\t"+"gz: "+String(gz);
  String str = str1+"   "+str2;
  writeSD(str);
  Serial.println(str);

  delay(1000);
  
}

void writeSD(String str){
  dataFile = SD.open("data.txt", FILE_WRITE);
  dataFile.println(str);
  dataFile.close();
}
