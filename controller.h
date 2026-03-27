
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "functions.h"

void pinInitializer()
{
  pinMode(displayButton, INPUT_PULLUP);
  
  pinMode(buzzer, OUTPUT);
  
  pinMode(PWMLCD, OUTPUT);
}

void Activity()
{
//Normal messages
  if(counter >= 0 && counter < 2000)
   {
     textScroll();
     counter++;
   }
   else if(counter >= 2000 && counter < 2001)
   {
     lcd.clear();
     bluetoothMessages();
     counter++;
   }
   else if(counter >= 2001 && counter < 2300)
   {     
     messageCurrentState();
     counter++;
   }
   else if(counter >= 2300)
   {
     messageInfo();
     counter = 0;     
   }
}

void displayInitializer()
{
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("  Starting The System...");
}

void Display()
{
//Button Value
  int theRawButton = digitalRead(displayButton);
  int theButton = map(theRawButton, 1, 0, 0, 1);
  
//Display Backlight Settings
  
  //Brightness Value
  int theBrightness = getBrightness();
  
    buffer[bufferIndex++]=theBrightness;
  
    if (bufferIndex >= dimBuffer)
      bufferIndex=0; 
   
    byte meanBrightness = mean();

  if(meanBrightness >= 140)
  {
    buffer[bufferIndex++]=theBrightness;
  
    if (bufferIndex >= dimBuffer)
      bufferIndex=0; 
   
    byte meanBrightness = mean();

    if(theButton == 1)
    {
      analogWrite(PWMLCD, meanBrightness);
    }
  
    else if(sensorValue <= 350 && FlameSensorValue > 500 && TMP < 45 && theButton == 0) //all off
    {
      analogWrite(PWMLCD, 0);
    }  
    else if(sensorValue > 350 && FlameSensorValue < 500 && TMP > 45 && theButton == 0) //all on
    {
      analogWrite(PWMLCD, meanBrightness);
    }
    
    else if(sensorValue > 350 && FlameSensorValue < 500 && TMP < 45 && theButton == 0) //gas + flame
    {
      analogWrite(PWMLCD, meanBrightness);
    }
    else if(sensorValue > 350 && FlameSensorValue > 500 && TMP > 45 && theButton == 0) //gas + TMP
    {
      analogWrite(PWMLCD, meanBrightness);
    }
    else if(sensorValue < 350 && FlameSensorValue < 500 && TMP > 45 && theButton == 0) //flame + TMP
    {
      analogWrite(PWMLCD, meanBrightness);
    }
    
    
    else if(sensorValue > 350 && FlameSensorValue > 500 && TMP < 45 && theButton == 0) //gas
    {
      analogWrite(PWMLCD, meanBrightness);
    }
    else if(sensorValue < 350 && FlameSensorValue > 500 && TMP > 45 && theButton == 0) //TMP
    {
      analogWrite(PWMLCD, meanBrightness);
    }
    else if(sensorValue < 350 && FlameSensorValue < 500 && TMP < 45 && theButton == 0) //flame
    {
      analogWrite(PWMLCD, meanBrightness);
    }   
  }
  else if(meanBrightness < 140)
  {
    byte meanBrightness = 140;

    if(theButton == 1)
    {
      analogWrite(PWMLCD, meanBrightness);
    }
  
    else if(sensorValue <= 350 && FlameSensorValue > 500 && TMP < 45 && theButton == 0) //all off
    {
      analogWrite(PWMLCD, 0);
    }  
    else if(sensorValue > 350 && FlameSensorValue < 500 && TMP > 45 && theButton == 0) //all on
    {
      analogWrite(PWMLCD, meanBrightness);
    }
    
    else if(sensorValue > 350 && FlameSensorValue < 500 && TMP < 45 && theButton == 0) //gas + flame
    {
      analogWrite(PWMLCD, meanBrightness);
    }
    else if(sensorValue > 350 && FlameSensorValue > 500 && TMP > 45 && theButton == 0) //gas + TMP
    {
      analogWrite(PWMLCD, meanBrightness);
    }
    else if(sensorValue < 350 && FlameSensorValue < 500 && TMP > 45 && theButton == 0) //flame + TMP
    {
      analogWrite(PWMLCD, meanBrightness);
    }
    
    
    else if(sensorValue > 350 && FlameSensorValue > 500 && TMP < 45 && theButton == 0) //gas
    {
      analogWrite(PWMLCD, meanBrightness);
    }
    else if(sensorValue < 350 && FlameSensorValue > 500 && TMP > 45 && theButton == 0) //TMP
    {
      analogWrite(PWMLCD, meanBrightness);
    }
    else if(sensorValue < 350 && FlameSensorValue < 500 && TMP < 45 && theButton == 0) //flame
    {
      analogWrite(PWMLCD, meanBrightness);
    }   
  }   
}

void Buzzer()
{  
//Buzzer
  if(sensorValue > 500 && FlameSensorValue < 70 && TMP > 45) //all on | Fire
  {
    soundBuzzerWarning();
  }
  else if(sensorValue > 350 && sensorValue < 500 && FlameSensorValue < 500 && TMP > 45) //all on | High Risk Fire
  {
    soundBuzzerWarning();
  }
  else if(sensorValue > 350 && sensorValue < 500 && FlameSensorValue < 500 && FlameSensorValue > 70 && TMP < 45) //gas + flame L
  {
    soundBuzzerSoftAlert();
  }
  else if(sensorValue > 500 && FlameSensorValue < 70 && TMP < 45) //gas + flame H
  {
    soundBuzzerWarning();
  }
  else if(sensorValue > 350 && sensorValue < 500 && FlameSensorValue > 500 && TMP > 45 && TMP < 60) //gas + TMP L
  {
    soundBuzzerSoftAlert();
  }
  else if(sensorValue > 500 && FlameSensorValue > 500 && TMP > 60) //gas + TMP H
  {
    soundBuzzerWarning();
  }
  else if(sensorValue < 350 && FlameSensorValue < 500 && FlameSensorValue > 70 && TMP > 45 && TMP < 60) //flame + TMP L
  {
    soundBuzzerSoftAlert();
  }
  else if(sensorValue < 350 && FlameSensorValue < 70 && TMP > 60) //flame + TMP H
  {
    soundBuzzerWarning();
  }
  else if(sensorValue > 350 && sensorValue < 500 && FlameSensorValue > 500 && TMP < 45) //gas L
  {
    soundBuzzerSoftAlert();
  }
  else if(sensorValue > 500 && FlameSensorValue > 500 && TMP < 45) //gas H
  {
    soundBuzzerWarning();
  }
  else if(sensorValue < 350 && FlameSensorValue > 500 && TMP > 45 && TMP < 60) //TMP L
  {
    soundBuzzerSoftAlert();
  }
  else if(sensorValue < 350 && FlameSensorValue > 500 && TMP > 60) //TMP H
  {
    soundBuzzerWarning();
  }
  else if(sensorValue < 350 && FlameSensorValue < 500 && FlameSensorValue > 70 && TMP < 45) //flame L
  {
    soundBuzzerSoftAlert();
  }
  else if(sensorValue < 350 && FlameSensorValue < 70 && TMP < 45) //flame H
  {
    soundBuzzerWarning();
  } 
}

#endif
