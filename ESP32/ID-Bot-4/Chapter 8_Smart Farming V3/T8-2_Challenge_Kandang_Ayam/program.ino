#define BLYNK_TEMPLATE_ID "TMPL4MwKiA1O"
#define BLYNK_DEVICE_NAME "Web Dashboard Smart Farming"
#define BLYNK_AUTH_TOKEN "7ux92fMqc7UjB_qNpPDc7u1C7n1FXeV-"

#define pinRelay 2
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h"
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 

Servo myservo;
const int DHT_PIN = 15;
DHTesp dhtSensor;
const float GAMMA = 0.7;
const float RL10 = 50;
float temperature = 0;
float humidity = 0;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

BlynkTimer timer;

void sendSensor()
{
  float analogValue = analogRead(34);
  float voltage = analogValue * 5/4095.0;
  float resistance = 2000 * voltage / (1 - voltage / 5);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
  Serial.print("Lux: ");
  Serial.println(lux);
  Blynk.virtualWrite(V1, lux);
  
  if (lux >= 50){
    Serial.print("Status: ");
    Serial.println("Terang");
    digitalWrite(pinRelay, HIGH);
  } else {
    Serial.print("Status: ");
    Serial.println("Gelap");
    digitalWrite(pinRelay, LOW);
  }
  delay(100);

  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  Serial.println("---");
  Blynk.virtualWrite(V2, data.temperature); 
  Blynk.virtualWrite(V3, data.humidity);

  humidity= data.humidity;
  temperature= data.temperature;
  lcd.setCursor(0,0);
  lcd.print("Humidty: ");
  lcd.print(humidity);
  lcd.print(" %");
  lcd.setCursor(0,1);
  lcd.print("Temperatur: ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0,2);
  lcd.print("Cahaya: ");
  lcd.print(lux);
  lcd.print(" lux");

  if (data.temperature <= 30 && data.humidity <= 30){
    Serial.print("Status: ");
    Serial.println("Dingin");
    myservo.write(180);
  } else {
    Serial.print("Status: ");
    Serial.println("Panas");
    myservo.write(90);
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

BLYNK_WRITE(V4) {
  int relayState = param.asInt();
  digitalWrite(pinRelay, relayState);
}

BLYNK_WRITE(V5){
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if (pinValue == 1){
    // do something when button is pressed;
    myservo.write(180);
    delay(2000);
  }
  else if (pinValue == 0) {
    // do something when button is released;
    myservo.write(0);
    delay(2000);
  }
}