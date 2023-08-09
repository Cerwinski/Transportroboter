#include "MeAuriga.h"

MeLineFollower lineFinder(PORT_3); 

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int sensorStatus = lineFinder.readSensors();
  switch(sensorStatus)
  {
    case S1_IN_S2_IN: Serial.println("Sensor 1 und 2 befinden sich inerhalb der schwarzen Linie"); break;
    case S1_IN_S2_OUT: Serial.println("Sensor 2 befindet sich außerhalb der schwarzen Linie"); break;
    case S1_OUT_S2_IN: Serial.println("Sensor 1 befindet sich außerhalb der schwarzen Linie"); break;
    case S1_OUT_S2_OUT: Serial.println("Sensor 1 und 2 befinden sich außerhalb der schwarzen Linie"); break;
    default: break;
  }
  delay(200);
}

