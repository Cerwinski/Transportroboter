#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeAuriga.h>

/**
 * @brief Pin Ports
 * 
 */
MeUltrasonicSensor ultrasonic_10(10);
MeEncoderOnBoard Encoder_1(SLOT1);
MeEncoderOnBoard Encoder_2(SLOT2);
Servo servo_6_1;
MePort port_6(6);
MeLightSensor lightsensor_12(12);

float distanceFromObstacle = 0;

/**
 * @brief Linksfahren
 * 
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
 * @brief Rechtsfahren
 * 
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
 * @brief Sekunden in Millisekunden
 * 
 * @param seconds 
 */
void _delay(float seconds) {
  if(seconds < 0.0){
    seconds = 0.0;
  }
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime) _loop();
}

/**
 * @brief Setup
 * 
 */
void setup() {
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);
  attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
  attachInterrupt(Encoder_2.getIntNum(), isr_process_encoder2, RISING);
  servo_6_1.attach(port_6.pin1());
  randomSeed((unsigned long)(lightsensor_12.read() * 123456));
  while(1) {
      distanceFromObstacle = ultrasonic_10.distanceCm();
      if(distanceFromObstacle > 3){
          Encoder_1.setTarPWM(0);
          Encoder_2.setTarPWM(0);
          _delay(0.5);

          servo_6_1.write(90);

          servo_6_1.write(0);

      }

      _loop();
  }

}

void _loop() {
}

/**
 * @brief Main Loop
 * 
 */
void loop() {
  _loop();
}