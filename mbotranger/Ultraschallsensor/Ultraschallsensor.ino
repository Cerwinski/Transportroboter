#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeAuriga.h>

MeUltrasonicSensor ultrasonic_10(10);  /// Initialisierung des Ultraschallsensors am Port 10
MeEncoderOnBoard Encoder_1(SLOT1);     /// Initialisierung des Encoders 1 im Slot 1
MeEncoderOnBoard Encoder_2(SLOT2);     /// Initialisierung des Encoders 2 im Slot 2
MeRGBLed rgbled_0(0, 12);              /// Initialisierung der RGB-LED am Port 0 und Pin 12
MeLightSensor lightsensor_12(12);      /// Initialisierung des Lichtsensors am Port 12

float distanceFromObstacle = 0;  /// Variable zur Speicherung der gemessenen Entfernung

void isr_process_encoder1(void)  /// Interrupt-Service-Routine für den ersten Encoder 
{
  if(digitalRead(Encoder_1.getPortB()) == 0){
    Encoder_1.pulsePosMinus();
  }else{
    Encoder_1.pulsePosPlus();
  }
}

void isr_process_encoder2(void)  /// Interrupt-Service-Routine für den zweiten Encoder 
{
  if(digitalRead(Encoder_2.getPortB()) == 0){
    Encoder_2.pulsePosMinus();
  }else{
    Encoder_2.pulsePosPlus();
  }
}

void _delay(float seconds) {  /// Funktion zum Verzögern für eine bestimmte Zeit
  if(seconds < 0.0){
    seconds = 0.0;
  }
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime) _loop();
}

void setup() {
  /// Konfiguration der Timer für Encoders und RGB-LED
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);

  /// Anhängen von Interrupts für Encoders
  attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
  attachInterrupt(Encoder_2.getIntNum(), isr_process_encoder2, RISING);

  rgbled_0.setpin(44);  /// Einstellen des Pins für die LED
  rgbled_0.fillPixelsBak(0, 2, 1);  // Aufleuchten der LED

  /// Initialisierung des Zufallsgenerators mit Lichtsensordaten
  randomSeed((unsigned long)(lightsensor_12.read() * 123456));

  while(1) {  /// Start einer Endlosschleife
      distanceFromObstacle = ultrasonic_10.distanceCm();  /// Messen der Entfernung zum Hindernis

      /// Wenn die Entfernung größer als 3 cm ist
      if(distanceFromObstacle > 3){
          /// Anhalten der Encoder
          Encoder_1.setTarPWM(0);
          Encoder_2.setTarPWM(0);
          _delay(0.5);  /// Verzögerung

          /// Einstellen der LED-Farbe auf Rot
          rgbled_0.setColor(0,255,0,0);
          rgbled_0.show();
          _delay(3);  /// Verzögerung

          /// Zurücksetzen der RGB-LED-Farbe
          rgbled_0.setColor(0,0,0,0);
          rgbled_0.show();
      }

      _loop();  
  }

}

void _loop() {
  
}

void loop() {
  _loop();  
}
