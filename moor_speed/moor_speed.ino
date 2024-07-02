#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
float rpm = 0;
int pid;
unsigned long millisBefore;
volatile int holes;
int TIP120pin = 11;
float setval = 5.00;
int a=130;
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Speed Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Test");
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), count, FALLING);
  pinMode(TIP120pin, OUTPUT); // Set pin for output to control TIP120 Base pin
analogWrite(TIP120pin, 100); // By changing values from 0 to 255 you can control motor speed
  delay(1000);
  lcd.clear();
   
}
void loop()
{
  print_to_LCD();
  if (millis() - millisBefore > 1000) {
    rpm = (holes / 12.0)/4;
    holes = 0;
    millisBefore = millis();
  }
  delay(1000);
 if(rpm > setval)
    { a=a-1; }
  else if(rpm < setval)
    { a=a+1; }
    else
    {      }
    analogWrite(TIP120pin, a);
}
void print_to_LCD() {
  lcd.setCursor(0, 0);
  lcd.print("Holes : ");
  lcd.print(holes);
  lcd.print("    ");
  lcd.setCursor(0, 1);
  lcd.print("RPM   : ");
  Serial.println(a);
  Serial.print("  ");
  Serial.println(rpm);
  lcd.print("    ");
}

void count() {
  holes++;
}
