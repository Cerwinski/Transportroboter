#include "MeColorSensor.h"
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeAuriga.h>

MeColorSensor colorsensor_8(8);
Servo servo_7_2;
MePort port_7(7);
Servo servo_7_1;
MeLightSensor lightsensor_12(12);

uint8_t detectedColor(MeColorSensor colorSensor, uint8_t colorType){
  if(colorType == colorSensor.Returnresult()){
    return 1;
  }
  return 0;
}

void _delay(float seconds) {
  if(seconds < 0.0){
    seconds = 0.0;
  }
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime) _loop();
}

void setup() {
  colorsensor_8.SensorInit();
  servo_7_2.attach(port_7.pin2());
  servo_7_1.attach(port_7.pin1());
  randomSeed((unsigned long)(lightsensor_12.read() * 123456));
  while(1) {
      if(detectedColor(colorsensor_8, 5)){

          servo_7_2.write(90);
          _delay(1);

          servo_7_1.write(90);
          _delay(1);

          servo_7_1.write(0);
          _delay(1);

          servo_7_2.write(0);

      }

      _loop();
  }

}

void _loop() {
}

void loop() {
  _loop();
}