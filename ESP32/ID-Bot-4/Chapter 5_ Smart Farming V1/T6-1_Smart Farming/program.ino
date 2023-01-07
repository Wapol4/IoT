
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL4MwKiA1O"
#define BLYNK_DEVICE_NAME "Web Dashboard Smart Farming"
#define BLYNK_AUTH_TOKEN "7ux92fMqc7UjB_qNpPDc7u1C7n1FXeV-"
#define LED 2

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h"

const int DHT_PIN = 15;
DHTesp dhtSensor;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

BlynkTimer timer;

void sendSensor()
{
 TempAndHumidity  data = dhtSensor.getTempAndHumidity();
 Serial.println("Temp: " + String(data.temperature, 2) + "°C");
 Serial.println("Humidity: " + String(data.humidity, 1) + "%");
 Serial.println("---");
 Blynk.virtualWrite(V0, data.temperature); 
 Blynk.virtualWrite(V1, data.humidity);//mengirimkan data ke Virtual pin di Blynk Cloud
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(LED, OUTPUT);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V2) {
  int ledState = param.asInt();
  digitalWrite(LED, ledState);
}