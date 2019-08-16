#include <LiquidCrystal.h>
#include "strings.h"
int health = 13;
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(health, OUTPUT);
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("GTA: Trainer");
}

void loop() {
    while(Serial.available() > 0) {
      lcd.setCursor(0, 1);
      lcd.print("AMMO: ");
      lcd.setCursor(6, 1);
      lcd.print(Serial.parseInt());
      if(Serial.parseInt() >= 2500) {
        digitalWrite(health, HIGH);
      } else if(Serial.parseInt() < 2500) {
        digitalWrite(health, 1);
        delay(100);
        digitalWrite(health, 0);
        delay(100);
      }
  }
}


