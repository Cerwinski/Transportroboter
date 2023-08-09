/**
 * @file main.cpp
 * @brief Hauptprogramm für mBot Ranger
 * @details Dieses Programm wurde von mBlock5 für den mBot Ranger generiert.
 *          Es enthält Bewegungs- und Sensorsteuerung für den Roboter.
 *          Die Kommentare wurden für die Verwendung mit Doxygen angepasst.
 */

#include "MeColorSensor.h"
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeAuriga.h>

MeLineFollower linefollower_9(9);
MeEncoderOnBoard Encoder_1(SLOT1);
MeEncoderOnBoard Encoder_2(SLOT2);
MeUltrasonicSensor ultrasonic_7(7);
MeRGBLed rgbled_0(0, 12);
Servo servo_10_2;
MePort port_10(10);
Servo servo_10_1;
MeColorSensor colorsensor_6(6);
MeLightSensor lightsensor_12(12);

float distanceFromObstacle = 0;

/**
 * @brief Interrupt-Service-Routine für Encoder 1
 */
void isr_process_encoder1(void)
{
  if(digitalRead(Encoder_1.getPortB()) == 0){
    Encoder_1.pulsePosMinus();
  }else{
    Encoder_1.pulsePosPlus();
  }
}

/**
 * @brief Interrupt-Service-Routine für Encoder 2
 */
void isr_process_encoder2(void)
{
  if(digitalRead(Encoder_2.getPortB()) == 0){
    Encoder_2.pulsePosMinus();
  }else{
    Encoder_2.pulsePosPlus();
  }
}

/**
 * @brief Bewegungsfunktion für den Roboter
 * @param direction Richtung (1: vorwärts, 2: rückwärts, 3: links, 4: rechts)
 * @param speed Geschwindigkeit (0-255)
 */
void move(int direction, int speed)
{
  int leftSpeed = 0;
  int rightSpeed = 0;
  if(direction == 1){
    leftSpeed = -speed;
    rightSpeed = speed;
  }else if(direction == 2){
    leftSpeed = speed;
    rightSpeed = -speed;
  }else if(direction == 3){
    leftSpeed = -speed;
    rightSpeed = -speed;
  }else if(direction == 4){
    leftSpeed = speed;
    rightSpeed = speed;
  }
  Encoder_1.setTarPWM(leftSpeed);
  Encoder_2.setTarPWM(rightSpeed);
}

/**
 * @brief Erkennt eine bestimmte Farbe
 * @param colorSensor Farbsensor
 * @param colorType Farbtyp
 * @return 1, wenn die Farbe erkannt wurde, sonst 0
 */
uint8_t detectedColor(MeColorSensor colorSensor, uint8_t colorType)
{
  if(colorType == colorSensor.Returnresult()){
    return 1;
  }
  return 0;
}

/**
 * @brief Verzögerungsfunktion in Sekunden
 * @param seconds Sekunden
 */
void _delay(float seconds) {
  if(seconds < 0.0){
    seconds = 0.0;
  }
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime) _loop();
}

/**
 * @brief Initialisierung des Roboters
 */
void setup() {
  // ...
}

/**
 * @brief Hauptprogrammschleife
 */
void _loop() {
  // ...
}

/**
 * @brief Endlosschleife des Hauptprogramms
 */
void loop() {
  // ...
}
