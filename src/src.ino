#include <LiquidCrystal.h>

//LCD pins
const int rs = 6, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int IRpin = A0;
int voltage = 0;

void setup()
{
  lcd.begin(16, 2);
  pinMode(IRpin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  voltage = analogRead(IRpin);
  lcd.setCursor(0,0);
  lcd.print("Voltage:");
  lcd.setCursor(0,1);
  lcd.print(voltage);
  Serial.println(voltage);
  delay(80);
}
