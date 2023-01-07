#include "Led.h"

#define ECHO_PIN 2
#define TRIG_PIN 15

int LED_YELLOW = 5;
int LED_BLUE = 18;
int LED_RED = 19;

Led led(LED_YELLOW, LED_BLUE, LED_RED);

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

float readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;

  Serial.print("Jarak: ");
  Serial.println(distance);

  if(distance > 50 && distance < 100){
    led.yellow();
  }else if (distance > 100 && distance < 200){
    led.blue();
  }else if(distance > 200 && distance < 300){
    led.red();
  }else if (distance > 300){
    led.all();
  }

}