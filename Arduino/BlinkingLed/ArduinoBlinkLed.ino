
#include "TrafficLight.h"

int LED_GREEN = 3;
int LED_YELLOW = 2;
int LED_RED = 4;

TrafficLight trafficLight(LED_GREEN, LED_YELLOW, LED_RED);

void setup() {
  
}

void loop() {
  
  trafficLight.green();
  delay(1000);
  
  trafficLight.red();
  delay(1000);

  trafficLight.yellow();
  delay(1000);

}
