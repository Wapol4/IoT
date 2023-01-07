#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

#define LEBAR_LAYAR 128 // Lebar layar OLED yang digunakan
#define TINGGI_LAYAR 64 // Tinggi layar OLED yang digunakan


Adafruit_SSD1306 oled(LEBAR_LAYAR, TINGGI_LAYAR, &Wire, -1);
const byte BARIS = 4; //Jumlah Baris Keypad
const byte KOLOM = 4; //Jumlah Kolom Keypad

char hexaKeys[BARIS][KOLOM] = {

  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}

};
byte rowPins[BARIS] = { 14, 12, 19, 18 };

byte colPins[KOLOM] = { 5, 4, 2, 15 };

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, BARIS, KOLOM);


void setup() {
  Serial.begin(9600);

  // initialize OLED display with I2C address 0x3C
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }

  delay(2000);         
  oled.clearDisplay(); // clear display

  oled.setTextSize(1);         // Atur ukuran text
  oled.setTextColor(WHITE);    // Atur warna text
  oled.setCursor(0, 10);       // Atur posisi text pada display
  oled.println("Keypad ESP32"); // Text yang dicetak
  delay(2000);
  oled.display(); 
  oled.clearDisplay();// menampilkan display OLED
}

void loop() {
  char customKey = customKeypad.getKey();
    if (customKey){

    oled.setTextSize(1);
    oled.setTextColor(WHITE); 
    oled.setCursor(0,10);
    oled.print("Press: ");
    oled.print(customKey);
    oled.display();

    delay(100);

  }
}
