
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TEMPLATE_ID"
#define BLYNK_DEVICE_NAME "Web Dashboard Smart Farming"
#define BLYNK_AUTH_TOKEN "BLYNK_AUTH_TOKEN-"
#define LED 2

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h"

const int DHT_PIN = 15;
DHTesp dhtSensor;
float temperature = 0;
float humidity = 0;

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

 // Testing Sensor
//  temperature = random(0, 110);
//  humidity = random(0, 90);

 Blynk.virtualWrite(V0, data.temperature); 
 Blynk.virtualWrite(V2, data.humidity);//mengirimkan data ke Virtual pin di Blynk Cloud

//  Blynk.virtualWrite(V0, temperature); 
//  Blynk.virtualWrite(V2, humidity);//mengirimkan data ke Virtual pin di Blynk Cloud

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