#define BLYNK_TEMPLATE_ID "BLYNK_TEMPLATE_ID"
#define BLYNK_DEVICE_NAME "Mobile Dashboard Smart Farming"
#define BLYNK_AUTH_TOKEN "BLYNK_AUTH_TOKEN"

#define pinRelay 2
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h"
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>    //Library LCD I2C
LiquidCrystal_I2C lcd(0x27,16,2);   //Alamat I2C

Servo myservo;
const int DHT_PIN = 15;
DHTesp dhtSensor;
const float GAMMA = 0.7;
const float RL10 = 50;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

BlynkTimer timer;
WidgetLCD lcd1(V9);
WidgetLCD lcd2(V10);

void sendSensor()
{
  float analogValue = analogRead(34);
  float voltage = analogValue * 5/4095.0;
  float resistance = 2000 * voltage / (1 - voltage / 5);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
  Serial.print("Lux: ");
  Serial.println(lux);
  Blynk.virtualWrite(V7, lux);
  
  if (lux >= 50){
    Serial.print("Status: ");
    Serial.println("Terang");
    // Blynk.virtualWrite(V8, HIGH);
  } else {
    Serial.print("Status: ");
    Serial.println("Gelap");
    // Blynk.virtualWrite(V8, LOW);
  }
  delay(100);

  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  Serial.println("---");
  Blynk.virtualWrite(V4, data.temperature); 
  Blynk.virtualWrite(V5, data.humidity);

  if (data.temperature <= 30 && data.humidity <= 30){
    Serial.print("Status: ");
    Serial.println("Dingin");
    lcd1.print(0, 1, "Dingin");
    lcd.clear();
  } else {
    Serial.print("Status: ");
    Serial.println("Panas");
    lcd2.print(0, 1, "Panas");
  }
  delay(100);
}

void setup()
{
  Serial.begin(115200);
  myservo.attach(26);
  pinMode(pinRelay, OUTPUT);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1L, sendSensor);
}

void loop()
{
  sendSensor();
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V8) {
  int relayState = param.asInt();
  if (relayState == 1){
    // do something when button is pressed;
     digitalWrite(pinRelay,HIGH);
  }
  else if (relayState == 0) {
    // do something when button is released;
     digitalWrite(pinRelay,LOW);
  }
}

BLYNK_WRITE(V2){
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if (pinValue == 0){
    // do something when button is pressed;
    myservo.write(90);
  }
  else if (pinValue == 1) {
    // do something when button is released;
    myservo.write(0);
  }
}