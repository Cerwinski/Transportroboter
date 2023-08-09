#include "MeAuriga.h"

MeUltrasonicSensor ultraSensor(PORT_7); 

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Abstand : ");
  Serial.print(ultraSensor.AbstandInCm() );
  Serial.println(" cm");
  delay(100); 
}
