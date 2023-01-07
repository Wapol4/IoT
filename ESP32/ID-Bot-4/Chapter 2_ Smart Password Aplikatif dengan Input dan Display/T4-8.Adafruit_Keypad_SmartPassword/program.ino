#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

#define TINGGI_LAYAR 64 // Tinggi layar OLED yang digunakan
#define LEBAR_LAYAR 128 // Lebar layar OLED yang digunakan

const byte ROWS = 4;    //Jumlah baris keypad
const byte COLS = 4;    //Jumlah kolom keypad

Adafruit_SSD1306 oled(LEBAR_LAYAR, TINGGI_LAYAR, &Wire, -1);

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
  Serial.begin(9600);

  // initialize OLED display with I2C address 0x3C
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }
  oled.clearDisplay();
  
  oled.setTextSize(1);         // Atur ukuran text
  oled.setTextColor(WHITE);    // Atur warna text
  oled.setCursor(20, 20);       // Atur posisi text pada display
  oled.println("SELAMAT DATANG"); // Text yang dicetak
  delay(2000);
  oled.display(); 
  oled.clearDisplay();// menampilkan display OLED
}

void loop() {
  oled.setTextSize(1);
  oled.setTextColor(WHITE); 
  oled.setCursor(0,0);
  oled.print("Input Password");      //Tampilan pada layar LCD
  
  customKey = customKeypad.getKey();    //Baca input keypad

  //------------Prosedur jika input berupa angka------------//
  switch(customKey){
    case '0' ... '9':
      oled.setTextSize(1);
      oled.setTextColor(WHITE); 
      oled.setCursor(0,10);
      number = number * 10 + (customKey - '0');
      oled.print(number);
      oled.display();
      oled.clearDisplay(); 
    break;

    //------------Jika input '#' maka cek password------------//
    case '#':
      if(number == password){          //Jika password benar, maka
        oled.setTextSize(1);
        oled.setTextColor(WHITE); 
        oled.setCursor(0,10);
        oled.print("Access Accepted ");  //Tampilan LCD
        number = 0;
        oled.display();
        oled.clearDisplay(); 
      }
      else{                             //Jika salah, maka
        oled.setTextSize(1);
        oled.setTextColor(WHITE); 
        oled.setCursor(0,10);
        oled.print("Invalid Password");  //Tampilan LCD
        oled.display();
        delay(2000);
        number = 0;
        oled.clearDisplay();
      }
    break;

    //------------Jika input '*' maka hapus tampilan------------//
    case '*':
      number = 0;
      oled.clearDisplay();
    break;
  }
}/* Program Kunci Pintu dengan password input Keypad 4x4 dibuat oleh Indobot */

