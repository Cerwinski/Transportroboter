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

uint8_t detectedColor(MeColorSensor colorSensor, uint8_t colorType) {
  if (colorType == colorSensor.Returnresult()) {
    return 1;
  }
  return 0;
}

/// Funktion zur Erkennung einer bestimmten Farbe durch den Farbsensor

void isr_process_encoder1(void) {
  if (digitalRead(Encoder_1.getPortB()) == 0) {
    Encoder_1.pulsePosMinus();
  } else {
    Encoder_1.pulsePosPlus();
  }
}

/// Interrupt-Service-Routine zur Verarbeitung der Encoder Signale am Slot 1

void isr_process_encoder2(void) {
  if (digitalRead(Encoder_2.getPortB()) == 0) {
    Encoder_2.pulsePosMinus();
  } else {
    Encoder_2.pulsePosPlus();
  }
}

/// Interrupt-Service-Routine zur Verarbeitung der EncoderSignale am Slot 2

void move(int direction, int speed) {
  /// Funktion zur Steuerung der Bewegung des Roboters basierend auf Richtung und Geschwindigkeit.
  /// Das Richtungsargument gibt die Bewegungsrichtung an, das Geschwindigkeitsargument steuert die Motorgeschwindigkeit.
  /// Das Verhalten der Motoren wird basierend auf den Richtungs- und Geschwindigkeitswerten angepasst.

  int leftSpeed = 0;
  int rightSpeed = 0;

  /// Initialisierung der Geschwindigkeitswerte für linke und rechte Motoren basierend auf der gewählten Richtung.

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

  /// Setzen des Ziel-PWM (Pulsweitenmodulation) für die Motorsteuerung

  Encoder_1.setTarPWM(leftSpeed);
  Encoder_2.setTarPWM(rightSpeed);
}

void _delay(float seconds) {
  if (seconds < 0.0) {
    seconds = 0.0;
  }
  long endTime = millis() + seconds * 1000;
  while (millis() < endTime) _loop();
}

/// Benutzerdefinierte Verzögerungsfunktion, die für eine angegebene Anzahl von Sekunden wartet, unter Verwendung der millis()-Funktion

void setup() {
  /// Setup-Funktion, die einmal ausgeführt wird, wenn der Arduino startet.

  randomSeed((unsigned long)(lightsensor_12.read() * 123456));
  /// Initialisieren des Zufallsgenerators mit der Lesung des Lichtsensors

  colorsensor_1.SensorInit();
  /// Initialisieren des Farbsensors

  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);
  /// Konfigurieren von Timern und Zählern für bestimmte Verhaltensweisen

  attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
  attachInterrupt(Encoder_2.getIntNum(), isr_process_encoder2, RISING);
  /// Anhängen von Interrupt-Routinen an die Encoder-Pins zur Verarbeitung der Encoder-Signale

  servo_10_1.attach(port_10.pin1());
  /// Anhängen des Servomotors an einen bestimmten Pin am Port 10

  if (detectedColor(colorsensor_1, 5)) {
    /// Überprüfen, ob eine bestimmte Farbe (Farbtyp 5) durch den Farbsensor erkannt wurde

    /// Bewegungen und Aktionen basierend auf der Farberkennung durchführen

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

void _loop() {
  /// Platzhalter Schleifenfunktion, die in der benutzerdefinierten Verzögerungsfunktion verwendet wird

  Encoder_1.loop();
  Encoder_2.loop();
}

/// Endlosschleife zur kontinuierlichen Durchführung der Encoder-Verarbeitungsroutinen

void loop() {
  _loop();
}

/// Die Haupt Endlosschleife die kontinuierlich läuft. Ruft die _loop()-Funktion auf.