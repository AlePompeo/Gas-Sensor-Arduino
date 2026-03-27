
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//Display Library & Setup
#include <LiquidCrystal.h>
LiquidCrystal lcd(3, 2, 4, 5, 6, 7);
//Math library
#include <math.h> 

//TEMPERATURE
// which analog pin to connect
#define THERMISTORPIN A4         
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 4000
// the value of the 'other' resistor
#define SERIESRESISTOR 1000
 
uint16_t samples[NUMSAMPLES];
int TMP = 0;


//INTS
//Buzzer
#define buzzer  11
//Gas Sensor
#define gasSensor  A0
int sensorValue = 0;
//Display
#define PWMLCD 9
#define lightSensor A5
#define displayButton 8
int counter = 0;
//Flame Sensor
#define FlameSensor A1
int FlameSensorValue = 0;
//Buffer
int dimBuffer = 550;
int buffer[550];
int bufferIndex = 0;
//Txt Scroll
byte scroll = 0;

//bufferSetup
void Memory() {
  for(int cnt=0;cnt<dimBuffer;cnt++)
    buffer[cnt]=0; 
}

//Mean
int mean()
{
  int retValue=0;
  long sum=0;
  
  for(int cnt=0;cnt<dimBuffer;cnt++)
    sum+=buffer[cnt]; 
   
  retValue = (int)(sum / (long)dimBuffer);  
  
  return retValue;
  
}

//Function

//Buzzer Functions
void soundBuzzerSoftAlert()
{
  tone(buzzer, 600, 1000);
  tone(buzzer, 0, 1000);
}

void soundBuzzerWarning()
{
  tone(buzzer, 2000, 300);
  tone(buzzer, 0, 100);
  tone(buzzer, 1000, 300);
  tone(buzzer, 0, 100);
}

//Bluetooth Macro
void bluetoothMessages()
{
  Serial.print(int(TMP) + String("°C"));
  Serial.print("|");
  Serial.print(int(sensorValue) + String(" ppm"));
  Serial.print("|");
  if(FlameSensorValue > 500)
  {
   Serial.println("No Fire");
  }
  else if(FlameSensorValue < 500)
  {
   Serial.println("Fire Risk");
  } 
}


//Display Messages
void textScroll()
{ 
  scroll++; 
  //Serial.println(scroll); 
  if(scroll>230)
  {  
    lcd.autoscroll();
    lcd.setCursor(0, 0);
    lcd.print(" ");
  }
  if(scroll>=231)
  {
    scroll=0;
  }
}

void messageInfo()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String("     Gas Value: ") + int(sensorValue) + String(" ppm"));
  lcd.setCursor(0, 1);
  lcd.print(String("    Temperature: ") + int(TMP) + char(223) + String("C"));
}

void messageCurrentState()
{
  if(sensorValue <= 350 && FlameSensorValue > 500 && TMP < 45) //all off
  {
    lcd.noAutoscroll();
    lcd.setCursor(0, 0);
    lcd.print("  No Problems   ");
    lcd.setCursor(0, 1);
    lcd.print(" were detected! ");
  }
  else if(sensorValue > 500 && FlameSensorValue < 70 && TMP > 45) //all on | Fire
  {
    if(counter >= 2002 && counter <= 2152)
    { 
    lcd.noAutoscroll();
    lcd.setCursor(0, 0);
    lcd.print("    WARNING!    ");
    }
    else if(counter > 2152 && counter < 2153)
    {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    }
    else if(counter > 2153 && counter < 2300)
    {      
    lcd.setCursor(0, 0);
    lcd.print("   GAS LEAKS!   ");
    lcd.setCursor(0, 1);
    lcd.print(" THERE IS FIRE! ");
    }
  }
  else if(sensorValue > 350 && sensorValue < 500 && FlameSensorValue < 500 && TMP > 45) //all on | High Risk Fire
  {
   if(counter >= 2002 && counter <= 2152)
    { 
      lcd.noAutoscroll();
      lcd.setCursor(0, 0);
      lcd.print("    WARNING!    ");
    }
    else if(counter > 2152 && counter < 2153)
    {      
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
    }
    else if(counter > 2153 && counter < 2300)
    {      
      lcd.setCursor(0, 0);
      lcd.print(" GAS LEAKS RISK ");
      lcd.setCursor(0, 1);
      lcd.print("   FIRE RISK!   ");
    }
  }
  else if(sensorValue > 350 && sensorValue < 500 && FlameSensorValue < 500 && FlameSensorValue > 70 && TMP < 45) //gas + flame L
  {
    lcd.noAutoscroll();
    lcd.setCursor(0, 0);
    lcd.print(" Gas Leaks Risk ");
    lcd.setCursor(0, 1);
    lcd.print("Flames Detected!");
  }
  else if(sensorValue > 500 && FlameSensorValue < 70 && TMP < 45) //gas + flame H
  {
   if(counter >= 2002 && counter <= 2152)
    {      
      lcd.noAutoscroll();
      lcd.setCursor(0, 0);
      lcd.print("    WARNING!    ");
    }
    else if(counter > 2152 && counter < 2153)
    {    
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
    }
    else if(counter > 2153 && counter < 2300)
    {      
      lcd.setCursor(0, 0);
      lcd.print("   GAS LEAKS!   ");
      lcd.setCursor(0, 1);
      lcd.print("FLAMES DETECTED!");
    }
  }
  else if(sensorValue > 350 && sensorValue < 500 && FlameSensorValue > 500 && TMP > 45 && TMP < 60) //gas + TMP L
  {
    lcd.noAutoscroll();
    lcd.setCursor(0, 0);
    lcd.print(" Gas Leaks Risk ");
    lcd.setCursor(0, 1);
    lcd.print("High Temperature");
  }
  else if(sensorValue > 500 && FlameSensorValue > 500 && TMP > 60) //gas + TMP H
  {
   if(counter >= 2002 && counter <= 2152)
    {      
      lcd.noAutoscroll();
      lcd.setCursor(0, 0);
      lcd.print("    WARNING!    ");
    }
    else if(counter > 2152 && counter < 2153)
    {        
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
    }
    else if(counter > 2153 && counter < 2300)
    {      
      lcd.setCursor(0, 0);
      lcd.print("   GAS LEAKS!   ");
      lcd.setCursor(0, 1);
      lcd.print(" TOO HIGH TEMP! ");
    }
  }
  else if(sensorValue < 350 && FlameSensorValue < 500 && FlameSensorValue > 70 && TMP > 45 && TMP < 60) //flame + TMP L
  {
    lcd.noAutoscroll();
    lcd.setCursor(0, 0);
    lcd.print("Flames Detected!");
    lcd.setCursor(0, 1);
    lcd.print("High Temperature");
  }
  else if(sensorValue < 350 && FlameSensorValue < 70 && TMP > 60) //flame + TMP H
  {
    if(counter >= 2002 && counter <= 2152)
    {    
      lcd.noAutoscroll();
      lcd.setCursor(0, 0);
      lcd.print("    WARNING!    ");
    }
    else if(counter > 2152 && counter < 2153)
    {    
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
    }
    else if(counter > 2153 && counter < 2300)
    {        
      lcd.setCursor(0, 0);
      lcd.print("   FIRE RISK!  ");
      lcd.setCursor(0, 1);
      lcd.print(" TOO HIGH TEMP!");
    }
  }
  else if(sensorValue > 350 && sensorValue < 500 && FlameSensorValue > 500 && TMP < 45) //gas L
  {
    lcd.noAutoscroll();
    lcd.setCursor(0, 0);
    lcd.print(" Gas Leaks Risk ");
  }
  else if(sensorValue > 500 && FlameSensorValue > 500 && TMP < 45) //gas H
  {
    if(counter >= 2002 && counter <= 2152)
    {
      lcd.noAutoscroll();
      lcd.setCursor(0, 0);
      lcd.print("    WARNING!    ");
    }
    else if(counter > 2152 && counter < 2153)
    {    
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
    }
    else if(counter > 2153 && counter < 2300)
    {    
      lcd.setCursor(0, 0);
      lcd.print("   GAS LEAKS!   ");
    }
  }
  else if(sensorValue < 350 && FlameSensorValue > 500 && TMP > 45 && TMP < 60) //TMP L
  {
    lcd.noAutoscroll();
    lcd.setCursor(0, 0);
    lcd.print("High Temperature");
  }
  else if(sensorValue < 350 && FlameSensorValue > 500 && TMP > 60) //TMP H
  {
    if(counter >= 2002 && counter <= 2152)
    {
      lcd.noAutoscroll();
      lcd.setCursor(0, 0);
      lcd.print("    WARNING!    ");
    }  
    else if(counter > 2152 && counter < 2153)
    {
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
    }
    else if(counter > 2153 && counter < 2300)
    {
      lcd.setCursor(0, 0);
      lcd.print("TOO HIGH TEMP!");
    }
  }
  else if(sensorValue < 350 && FlameSensorValue < 500 && FlameSensorValue > 70 && TMP < 45) //flame L
  {
    lcd.noAutoscroll();
    lcd.setCursor(0, 0);
    lcd.print("Flames Detected!");
  }
  else if(sensorValue < 350 && FlameSensorValue < 70 && TMP < 45) //flame H
  {
    if(counter >= 2002 && counter <= 2152)
    {
      lcd.noAutoscroll();
      lcd.setCursor(0, 0);
      lcd.print("    WARNING!    ");
    }
    else if(counter > 2152 && counter < 2153)
    {
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
    }
    else if(counter > 2153 && counter < 2300)
    {
      lcd.setCursor(0, 0);
      lcd.print("   FIRE RISK!  ");
    }
  }    
}

float getTemperature()
{
  //TEMPERATURE
  uint8_t i;
  float average;
 
  // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++) {
   samples[i] = analogRead(THERMISTORPIN);
  }
 
  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  }
  average /= NUMSAMPLES;
 
  //Serial.print("Average analog reading "); 
  //Serial.println(average);
 
  // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
  //Serial.print("Thermistor resistance "); 
  //Serial.println(average);
 
  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C
  TMP = steinhart - 0.5;

  return TMP;
 
  //Serial.print("Temperature "); 
  //Serial.print(TMP);
  //Serial.println(" *C");
}

int getBrightness()
{
  //Light Sensor Value
  int rawLightSensor = analogRead(lightSensor);
  auto lightParabola = (float(1/511.5) * long(rawLightSensor*rawLightSensor)) + ((- 2)*(rawLightSensor)) + 1023;
  auto abslightparabola = abs(lightParabola);
  auto mappedAbsLightParabola = float(int(abslightparabola)/float(1023/255));
  //Serial.println(mappedAbsLightParabola);

  return mappedAbsLightParabola;
}

#endif
