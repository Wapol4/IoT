#include <Wire.h>
#include <LiquidCrystal_I2C.h>    //Library LCD I2C
LiquidCrystal_I2C lcd(0x27,16,2);   //Alamat I2C
#include <Keypad.h>
#include <ESP32Servo.h>

#define TINGGI_LAYAR 64 // Tinggi layar OLED yang digunakan
#define LEBAR_LAYAR 128 // Lebar layar OLED yang digunakan

Servo myservo;
const byte ROWS = 4;    //Jumlah baris keypad
const byte COLS = 4;    //Jumlah kolom keypad

int buzzer = 25;

// Adafruit_SSD1306 oled(LEBAR_LAYAR, TINGGI_LAYAR, &Wire, -1);

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
String password = "";    //Password
String memory = "";

int buku = 0;
bool isBuku = false;

void setup() {
  Serial.begin(9600);
  myservo.attach(26);
  pinMode(buzzer, OUTPUT);

  lcd.init ();              //Mulai LCD
  lcd.setBacklight(HIGH);   //Nyalakan backlight

  lcd.setCursor(0,0);
  lcd.print("SELAMAT DATANG");
  lcd.setCursor(0,1);
  lcd.print("PERPUSTAKAAN");
  delay(2000);
  lcd.clear();
  
}

void loop() {
  customKey = customKeypad.getKey();    //Baca input keypad

  //------------Prosedur jika input berupa angka------------//
  switch(customKey){
    case '0' ... '9':
      lcd.setCursor(0,1);
      number = number * 10 + (customKey - '0');
      memory = String(number);
      lcd.print(memory);
    break;

    //------------Jika input '#' maka cek password------------//
    case '#':
      if(String(number) == password){          //Jika password benar, maka
        lcd.setCursor(0,1);
        lcd.print("Access Accepted ");  //Tampilan LCD
        number = 0;
        myservo.write(180);
        delay(5000);
        myservo.write(90);
        
      }
    //   else{                             //Jika salah, maka
    //     oled.setTextSize(1);
    //     oled.setTextColor(WHITE); 
    //     oled.setCursor(0,10);
    //     oled.print("Invalid Password");  //Tampilan LCD
    //     oled.display();
    //     digitalWrite(buzzer, HIGH);
    //     delay(2000);
    //     number = 0;
    //     oled.clearDisplay();
    //   }
    // break;

    //------------Jika input '*' maka hapus tampilan------------//
    case 'A':
      lcd.setCursor(0,0);
      lcd.print("Password : ");
      lcd.setCursor(10,0);
      password = memory;
      lcd.print(password);
      delay(3000);
      break;

    case 'B':
      lcd.setCursor(0,0);
      lcd.print("Masukkan Password : ");
      delay(3000);
      break;

    case 'C':
      lcd.setCursor(0,0);
      lcd.print("Masukkan Barang : ");
      buku += 1;
      delay(3000);
      break;

    case 'D':
      lcd.setCursor(0,0);
      lcd.print("Jumlah Buku: ");
      lcd.setCursor(0,1);
      lcd.print("Buku : ");
      lcd.setCursor(10,1);
      lcd.print(buku);
      delay(3000);
      break;

    case '*':
      number = 0;
      lcd.clear();
    break;
  }
}
/* Program Kunci Pintu dengan password input Keypad 4x4 dibuat oleh Indobot */

