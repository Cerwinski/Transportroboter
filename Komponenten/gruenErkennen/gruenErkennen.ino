#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeAuriga.h>
#include "MeColorSensor.h"


MeLightSensor lightsensor_12(12);
MeColorSensor colorsensor_1(1);
MeEncoderOnBoard Encoder_1(SLOT1);
MeEncoderOnBoard Encoder_2(SLOT2);
Servo servo_10_1;
MePort port_10(10);

float distanceFromObstacle = 0;

/**
 * @brief Funktion zur Erkennung einer bestimmten Farbe durch den Farbsensor
 * 
 * @param colorSensor 
 * @param colorType 
 * @return uint8_t 
 */
uint8_t detectedColor(MeColorSensor colorSensor, uint8_t colorType) {
  if (colorType == colorSensor.Returnresult()) {
    return 1;
  }
  return 0;
}


/**
 * @brief Interrupt-Service-Routine zur Verarbeitung der Encoder Signale am Slot 1
 * 
 */
void isr_process_encoder1(void) {
  if (digitalRead(Encoder_1.getPortB()) == 0) {
    Encoder_1.pulsePosMinus();
  } else {
    Encoder_1.pulsePosPlus();
  }
}

/**
 * @brief Interrupt-Service-Routine zur Verarbeitung der EncoderSignale am Slot 2
 * 
 */
void isr_process_encoder2(void) {
  if (digitalRead(Encoder_2.getPortB()) == 0) {
    Encoder_2.pulsePosMinus();
  } else {
    Encoder_2.pulsePosPlus();
  }
}


/**
 * @brief Funktion zur Steuerung der Bewegung des Roboters basierend auf Richtung und Geschwindigkeit.
          Das Richtungsargument gibt die Bewegungsrichtung an, das Geschwindigkeitsargument steuert die Motorgeschwindigkeit.
          Das Verhalten der Motoren wird basierend auf den Richtungs- und Geschwindigkeitswerten angepasst.
 * 
 * @param direction 
 * @param speed 
 */

void move(int direction, int speed) {

  int leftSpeed = 0;
  int rightSpeed = 0;

  /**
   * @brief Construct a new if object
   * 
   */

  if (direction == 1) {
    leftSpeed = -speed;
    rightSpeed = speed;
  } else if (direction == 2) {
    leftSpeed = speed;
    rightSpeed = -speed;
  } else if (direction == 3) {
    leftSpeed = -speed;
    rightSpeed = -speed;
  } else if (direction == 4) {
    leftSpeed = speed;
    rightSpeed = speed;
  }

  Encoder_1.setTarPWM(leftSpeed);
  Encoder_2.setTarPWM(rightSpeed);
}

/**
 * @brief Sekunden in Millisekunden
 * 
 * @param seconds 
 */
void _delay(float seconds) {
  if (seconds < 0.0) {
    seconds = 0.0;
  }
  long endTime = millis() + seconds * 1000;
  while (millis() < endTime) _loop();
}

/**
 * @brief Setup
 * 
 */
void setup() {

  randomSeed((unsigned long)(lightsensor_12.read() * 123456));

  colorsensor_1.SensorInit();

  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);

  attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
  attachInterrupt(Encoder_2.getIntNum(), isr_process_encoder2, RISING);

  servo_10_1.attach(port_10.pin1());

  if (detectedColor(colorsensor_1, 5)) {

    move(4, 39 / 100.0 * 255);
    _delay(1);
    move(4, 0);

    move(1, 30 / 100.0 * 255);
    _delay(2);
    move(1, 0);
    _delay(1);

    servo_10_1.write(0);
    _delay(1);

    move(2, 30 / 100.0 * 255);
    _delay(1);
    move(2, 0);

    move(4, 30 / 100.0 * 255);
    _delay(3);
    move(4, 0);

    move(1, 100 / 100.0 * 255);
    _delay(4);
    move(1, 0);
  }
}

/**
 * @brief Platzhalter Schleifenfunktion, die in der benutzerdefinierten Verzögerungsfunktion verwendet wird
 * 
 */
void _loop() {

  Encoder_1.loop();
  Encoder_2.loop();
}

/**
 * @brief Die Haupt Endlosschleife die kontinuierlich läuft. Ruft die _loop()-Funktion auf.
 * 
 */
void loop() {
  _loop();
}