#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LEBAR_LAYAR 128 // Lebar layar OLED yang digunakan
#define TINGGI_LAYAR 64 // Tinggi layar OLED yang digunakan


Adafruit_SSD1306 oled(LEBAR_LAYAR, TINGGI_LAYAR, &Wire, -1);

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
  oled.println("Hello World"); // Text yang dicetak
  oled.display();              // menampilkan display OLED
}

void loop() {
}