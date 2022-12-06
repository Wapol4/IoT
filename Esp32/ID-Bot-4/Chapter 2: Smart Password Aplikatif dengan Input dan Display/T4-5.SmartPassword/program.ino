#include <Keypad.h>                 //Library keypad
#include <LiquidCrystal_I2C.h>    //Library LCD I2C
LiquidCrystal_I2C lcd(0x27,16,2);   //Alamat I2C

const byte ROWS = 4;    //Jumlah baris keypad
const byte COLS = 4;    //Jumlah kolom keypad

int LED_1 = 33;
int LED_2 = 32;

char Keys[ROWS][COLS] = {   //Membuat array keypad
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { 14, 12, 19, 18 }; 
byte colPins[COLS] = { 5, 4, 2, 15 };

Keypad customKeypad = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS);    //Masukkan info keypad pada library


char customKey;         //Variabel penampung input keypad
int number = 0;         //Variabel penampung nilai angka
int password = 1379;    //Password

void setup() {
  lcd.init ();              //Mulai LCD
  lcd.setBacklight(HIGH);   //Nyalakan backlight
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Input Password");      //Tampilan pada layar LCD
  
  customKey = customKeypad.getKey();    //Baca input keypad

  //------------Prosedur jika input berupa angka------------//
  switch(customKey){
    case '0' ... '9':
      lcd.setCursor(0,1);
      number = number * 10 + (customKey - '0');
      lcd.print(number);
    break;

    //------------Jika input '#' maka cek password------------//
    case '#':
      if(number == password){           //Jika password benar, maka
        lcd.setCursor(0,1);
        lcd.print("Access Accepted ");  //Tampilan LCD
        number = 0;
        lcd.clear(); 
        digitalWrite(LED_1, HIGH);
        digitalWrite(LED_2, LOW);
        delay(1000);
      }
      else{                             //Jika salah, maka
        lcd.setCursor(0,1);
        lcd.print("Invalid Password");  //Tampilan LCD
        delay(2000);
        number = 0;
        lcd.clear();
        digitalWrite(LED_1, LOW);
        digitalWrite(LED_2, HIGH);
        delay(1000);
      }
    break;

    //------------Jika input '*' maka hapus tampilan------------//
    case '*':
      number = 0;
      lcd.clear();
    break;
  }
}/* Program Kunci Pintu dengan password input Keypad 4x4 dibuat oleh Indobot */

