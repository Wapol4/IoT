#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  

void setup()
{
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Nama : ");
  lcd.setCursor(6,0);
  lcd.print("Airis");
  lcd.setCursor(0,1);
  lcd.print("Asal : ");
  lcd.setCursor(6,1);
  lcd.print("Jakarta");
}


void loop()
{
}
