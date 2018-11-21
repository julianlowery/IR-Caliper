#include <LiquidCrystal.h>

//LCD pins
const int rs = 6, en = A5, d4 = A4, d5 = A3, d6 = A2, d7 = A1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int IRpin = A0;
int voltage = 0;
int buttonPin = 8;

void setup()
{
  lcd.begin(16, 2);
  pinMode(IRpin, INPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  if(digitalRead(buttonPin) == HIGH)
  {
    lcd.clear();
    const int numSamples = 50;
    
    int samples[numSamples] = {0};
    int sum = 0;
    int validInputs = numSamples;
    
    for(int index = 0; index < numSamples; index++)
    {
      samples[index] = analogRead(IRpin);
      sum += samples[index];
      delay(30);
    }

    for(int i = 0; i < numSamples; i++)
    {
      int min_ = 10000;
  
      for(int j = i; j < numSamples; j++)
      {
        if(samples[j] < min_)
        {
          int temp_ = min_;
          min_ = samples[j];
          samples[j] = temp_;
        }
      }
      samples[i] = min_;
    }

    int q1 = (numSamples + 1) / 4;

    int quartile1 = samples[q1];

    int q3 = (3*(numSamples + 1)) / 4;

    int quartile3 = samples[q3];

    int iqr = quartile3 - quartile1;

    int upperBound = quartile3 + (1.5 * iqr);

    int lowerBound = quartile1 - (1.5 * iqr);

    int newSum = 0;

    for(int index = 0; index < numSamples; index++)
    {
      if(samples[index] < lowerBound || samples[index] > upperBound)
      {
        samples[index] = 0;
        validInputs--;
      }
        newSum += samples[index];
    }

    int newMean = newSum / validInputs;

    float output = (-0.001 * (newMean)*(newMean) + 1.202*(newMean) - 249.13);

    lcd.setCursor(0,0);
    lcd.print("distance:");
    lcd.setCursor(0,1);
//    lcd.print(newMean);
    lcd.print(output);
    lcd.print(" mm");
    delay(2000);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Push Button");
  delay(100);
}
