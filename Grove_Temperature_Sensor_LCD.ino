#include "rgb_lcd.h"

// define and instantiate lcd object
rgb_lcd lcd;

// define lcd background color
const int colorR = 0;
const int colorG = 0;
const int colorB = 255;

// temp sensor
const int pinTemp = A0;      // pin of temperature sensor
float temperature;
int B=3975;                  // B value of the thermistor
float resistance;

// fan
int motorPin = 9; // pin of the base of motor transistor

// threshold
const int potentiometer = A1; // rotary angle sensor connect to A1
float threshold;

void setup()
{
    // set up the LCD's number of columns and rows:
    lcd.begin(36, 2);
    lcd.setRGB(colorR, colorG, colorB);

    // threshold control
    pinMode(potentiometer, INPUT);
}

void loop()
{
    int tmp_val = analogRead(pinTemp);                           // get temp analog value from temp sensor
    resistance=(float)(1023-tmp_val)*10000/tmp_val;              // get resistance
    temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;     // calc current temperature

    // calculate threshold
    int thr_val = analogRead(potentiometer);                   // get threshold analog value from potentiometer
    threshold=(float)(1023-thr_val)*60/1023;                   // calc threshold temperature
    
    // col 0, row 0
    lcd.setCursor(0, 0);
    lcd.print("Curr temp=");
    lcd.print(temperature);
     
    // col 0, row 1
    lcd.setCursor(0, 1);
    lcd.print("Threshold=");
    lcd.print(threshold);
 
    
    // turn on the base of motor transitor 
    if (temperature > threshold) {
      analogWrite(motorPin, 3*(temperature-threshold));
    } else {
      analogWrite(motorPin, 0);
    }
    
    delay(1000);          // loop delay 1s
}
