#include "MeColorSensor.h"
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeAuriga.h>

/**
 * @brief Port Pins
 * 
 */
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

/**
 * @brief Variable Abstand zum Objekt
 * 
 */
float distanceFromObstacle = 0;

/**
 * @brief linker Motor
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
 * @brief rechter Motor
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
 * @brief Links, Rechts, Gerade aus und rückwärts fahren
 * 
 * @param direction 
 * @param speed 
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
 * @brief Farben erkennen durch den Farbsensor
 * 
 * @param colorSensor 
 * @param colorType 
 * @return uint8_t 
 */
uint8_t detectedColor(MeColorSensor colorSensor, uint8_t colorType){
  if(colorType == colorSensor.Returnresult()){
    return 1;
  }
  return 0;
}

/**
 * @brief Sekunden in Millisekunden umwandeln für den delay
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
  rgbled_0.setpin(44);
  rgbled_0.fillPixelsBak(0, 2, 1);
  servo_10_2.attach(port_10.pin2());
  servo_10_1.attach(port_10.pin1());
  colorsensor_6.SensorInit();
  randomSeed((unsigned long)(lightsensor_12.read() * 123456));
  while(1) {

    /**
     * @brief Wenn der Linienfolgesensor rechts weiß sieht und schwarz links, dann soll er nach rechts fahren.
     * 
     */
      if((0?(2==0?linefollower_9.readSensors()==0:(linefollower_9.readSensors() & 2)==2):(2==0?linefollower_9.readSensors()==3:(linefollower_9.readSensors() & 2)==0))){
          if((1?(1==0?linefollower_9.readSensors()==0:(linefollower_9.readSensors() & 1)==1):(1==0?linefollower_9.readSensors()==3:(linefollower_9.readSensors() & 1)==0))){

              Encoder_1.setTarPWM(-1 * 15/100.0*255);
              Encoder_2.setTarPWM(0/100.0*255);

          }

      }

      /**
       * @brief Wenn der Linienfolgesensor rechts schwarz sieht und weiß links, dann soll er nach links fahren.
       * 
       */
      if((0?(1==0?linefollower_9.readSensors()==0:(linefollower_9.readSensors() & 1)==1):(1==0?linefollower_9.readSensors()==3:(linefollower_9.readSensors() & 1)==0))){
          if((1?(2==0?linefollower_9.readSensors()==0:(linefollower_9.readSensors() & 2)==2):(2==0?linefollower_9.readSensors()==3:(linefollower_9.readSensors() & 2)==0))){

              Encoder_1.setTarPWM(-1 * 0/100.0*255);
              Encoder_2.setTarPWM(15/100.0*255);

          }

      }
      
      /**
       * @brief Wenn der Linienfolgesensor nur schwarz erkennt, dann soll er gerade fahren.
       * 
       */
      if((0?(3==0?linefollower_9.readSensors()==0:(linefollower_9.readSensors() & 3)==3):(3==0?linefollower_9.readSensors()==3:(linefollower_9.readSensors() & 3)==0))){

          Encoder_1.setTarPWM(-1 * 20/100.0*255);
          Encoder_2.setTarPWM(20/100.0*255);

      }

      /**
       * @brief Wenn er ein Objekt erkennt, was weniger als 10cm entfernt ist, dann soll er grün leuchten und sich zu dem Objekt bewegen. Dann soll er das Objekt greifen, der Linearantrieb fährt das Objekt hoch, damit es nicht am Boden schleift.
       * 
       */
      distanceFromObstacle = ultrasonic_7.distanceCm();
      if(distanceFromObstacle < 10){
          Encoder_1.setTarPWM(0);
          Encoder_2.setTarPWM(0);
          _delay(0.5);

          rgbled_0.setColor(0,15,162,0);
          rgbled_0.show();

          servo_10_2.write(0);
          _delay(1);

          servo_10_1.write(0);
          _delay(1);

          move(1, 15 / 100.0 * 255);
          _delay(1.5);
          move(1, 0);
          _delay(1);

          servo_10_1.write(90);
          _delay(1);

          servo_10_2.write(90);
          _delay(1);

      }

      /**
       * @brief Wenn er rot sieht, dann soll er die LED anmachen und rot leuchten und soll das Objekt ablegen. 
       * 
       */
      if(((1?(3==0?linefollower_9.readSensors()==0:(linefollower_9.readSensors() & 3)==3):(3==0?linefollower_9.readSensors()==3:(linefollower_9.readSensors() & 3)==0)))  &&  (detectedColor(colorsensor_6, 2))){

          move(1, 15 / 100.0 * 255);
          _delay(1);
          move(1, 0);

          move(4, 15 / 100.0 * 255);
          _delay(1.5);
          move(4, 0);

          rgbled_0.setColor(0,255,0,0);
          rgbled_0.show();

          servo_10_2.write(0);
          _delay(3);

          servo_10_1.write(0);
          _delay(1);

          move(2, 15 / 100.0 * 255);
          _delay(1);
          move(2, 0);

          move(3, 15 / 100.0 * 255);
          _delay(1.5);
          move(3, 0);

      }

      /**
       * @brief Zielort ist blau
       * 
       */
      if(((1?(3==0?linefollower_9.readSensors()==0:(linefollower_9.readSensors() & 3)==3):(3==0?linefollower_9.readSensors()==3:(linefollower_9.readSensors() & 3)==0)))  &&  (detectedColor(colorsensor_6, 7))){
          Encoder_1.setTarPWM(0);
          Encoder_2.setTarPWM(0);
          _delay(0.5);

      }

      _loop();
  }

}

/**
 * @brief Loop für das Fahren auf den Linien
 * 
 */
void _loop() {
  Encoder_1.loop();
  Encoder_2.loop();
}

/**
 * @brief Main loop
 * 
 */
void loop() {
  _loop();
}