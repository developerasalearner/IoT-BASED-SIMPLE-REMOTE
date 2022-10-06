#include "Arduino.h"
#include "Lcd.h"
#define LCD_ADDRESS 0x20
#define LCD_ROWS 2
#define LCD_COLUMNS 16
#define BACKLIGHT 255
#define KEYPAD A0
Lcd mylcd;
void setup() 
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  mylcd.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, BACKLIGHT);
  mylcd.clear();
}
void loop()
{
  int r;
    char ch;
    int pr=0;
    r=analogRead(KEYPAD);
    if(pr!=r)
    {
      if(r==68)
      {
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(9, HIGH);
        delay(50);
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        delay(50);
        mylcd.clear();
        mylcd.setCursor(0,0);
        mylcd.print("SELECT ONE");
        delay(100);
    
        mylcd.clear();
        mylcd.setCursor(0,0);
        mylcd.print("1 for FAN1");
        mylcd.setCursor(0,1);
        mylcd.print("2 for TV");
        delay(100);
        mylcd.clear();
        mylcd.setCursor(0,0);
        mylcd.print("3 for AC");
        mylcd.setCursor(0,1);
        mylcd.print("4 for S_PLUGE");
        delay(100);
        mylcd.clear();
        mylcd.setCursor(0,0);
        mylcd.print("5 for FAN2");
        mylcd.setCursor(0,1);
        mylcd.print("6 for DESKTOP");
        delay(100);
        mylcd.clear();
        mylcd.setCursor(0,0);
        mylcd.print("7 for LIGHT1");
        mylcd.setCursor(0,1);
        mylcd.print("8 for LIGHT2");
        delay(100);
        mylcd.clear();
        mylcd.setCursor(0,0);
        mylcd.print("To see the previ");
        mylcd.setCursor(0,1);
        mylcd.print("ous opt click");
        delay(100);
        mylcd.clear();
        mylcd.setCursor(0,0);
        mylcd.print("'ON'again");
        delay(100);
      }
      if(r==98)
      {
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        mylcd.clear();
        mylcd.setCursor(0,0);
        mylcd.print("FAN1 is ON");
        delay(100);
      }
      if(r==90)
      {
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        mylcd.clear();
        mylcd.setCursor(0,0);
        mylcd.print("TV is ON");
        delay(100);
      }
      if(r==83)
      {
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        mylcd.clear();
        mylcd.setCursor(0,0);
        mylcd.print("AC is ON");
        delay(100);
      }
      if(r==180)
      {
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        mylcd.clear();
        mylcd.setCursor(0,0);
        mylcd.print("S_PLUGE is ON");
        delay(100);
      }
      if(r==153)
      {
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        mylcd.clear();
        mylcd.setCursor(0,0);
        mylcd.print("FAN2 is ON");
        delay(100);
      }
      if(r==133)
      {
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        mylcd.clear();
        mylcd.setCursor(0,0);
        mylcd.print("DESKTOP is ON");
        delay(100);
      }
      if(r==1023)
      {
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);
        mylcd.clear();
        mylcd.setCursor(0,0);
        mylcd.print("LIGHT1 is ON");
        delay(100);
      }
      if(r==512)
      {
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, HIGH);
        mylcd.clear();
        mylcd.setCursor(0,0);
        mylcd.print("LIGHT2 is ON");
        delay(100);
      }
      pr=r;
    }
}
char readKeypad(int scancode)
 {
    if((scancode>=240)&&(scancode<=244))
    {
      return '1';
    }
    
 }
