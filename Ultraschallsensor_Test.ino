#include "MeAuriga.h"

MeColorSensor colorSensor(PORT_6);

uint8_t colorResult;
uint16_t redValue = 0, greenValue = 0, blueValue = 0, colorValue = 0;
uint8_t grayscaleValue = 0;
long sysTime = 0, colorCode = 0;

void setup() {
  Serial.begin(115200);
  colorSensor.SensorInit();
  sysTime = millis();
}

void loop() {
  if (millis() - sysTime > 200) {
    sysTime = millis();
    colorResult = colorSensor.ReturnResult();
    redValue = colorSensor.ReturnRedData();
    greenValue = colorSensor.ReturnGreenData();
    blueValue = colorSensor.ReturnBlueData();
    colorValue = colorSensor.ReturnColorData();
    colorCode = colorSensor.ReturnColorCode();
    grayscaleValue = colorSensor.ReturnGrayscale();

    Serial.print("R:");
    Serial.print(redValue);
    Serial.print("\t");
    Serial.print("G:");
    Serial.print(greenValue);
    Serial.print("\t");
    Serial.print("B:");
    Serial.print(blueValue);
    Serial.print("\t");
    Serial.print("C:");
    Serial.print(colorValue);
    Serial.print("\t");
    Serial.print("color:");

    switch (colorResult) {
      case BLACK:
        Serial.print("BLACK");
        break;
      case BLUE:
        Serial.print("BLUE");
        break;
    
      case GREEN:
        Serial.print("GREEN");
        break;
      case RED:
        Serial.print("RED");
        break;
      case WHITE:
        Serial.print("WHITE");
        break;
      default:
        break;
    }

    Serial.print("\t");
    Serial.print("code:");
    Serial.print(colorCode, HEX);
    Serial.print("\t");
    Serial.print("grayscale:");
    Serial.println(grayscaleValue);
  }
}