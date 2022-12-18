
#include "TrafficLight.h"
#include "Button.h"

int LED_GREEN = 3;
int LED_YELLOW = 2;
int LED_RED = 4;
int BUTTON = 10;

TrafficLight trafficLight(LED_GREEN, LED_YELLOW, LED_RED);
Button button(BUTTON);

void setup() {
  
}

void loop() {
  if(button.isPressed()){
    trafficLight.green();
    delay(1000);
  } else {
    trafficLight.red();
    delay(1000);
  }

  // trafficLight.yellow();
  // delay(1000);

}
