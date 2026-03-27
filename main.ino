
#include "controller.h"

void setup()  
{
  Serial.begin(9600);
  pinInitializer();  
  displayInitializer();
}

void loop() 
{
//Gas Sensor Value  
  sensorValue = analogRead(gasSensor);
//Temperature Value  
  TMP = getTemperature();
//Flame Sensor Value
  FlameSensorValue = analogRead(FlameSensor);  

  Buzzer();

  Display();
  
  Activity();

}
                       
