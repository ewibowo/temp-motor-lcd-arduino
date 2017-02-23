// demo of Starter Kit V2.0 - Grove Temperature Sensor
//
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 0;
const int colorG = 0;
const int colorB = 255;

const int pinTemp = A0;      // pin of temperature sensor

float temperature;
int B=3975;                  // B value of the thermistor
float resistance;

int motorPin = 9;

void setup()
{
    Serial.begin(9600);

    // set up the LCD's number of columns and rows:
    lcd.begin(36, 2);
    lcd.setRGB(colorR, colorG, colorB);
    
}

void loop()
{
    int val = analogRead(pinTemp);                               // get analog value
    resistance=(float)(1023-val)*10000/val;                      // get resistance
    temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;     // calc temperature
    Serial.println(temperature);
    // col 0, row 0
    lcd.setCursor(0, 0);
    lcd.print("Temp in Celsius:");
        
    // col 0, row 1
    lcd.setCursor(0, 1);
    lcd.print(temperature);

    analogWrite(motorPin,temperature);
    
    delay(1000);          // delay 1s
}
