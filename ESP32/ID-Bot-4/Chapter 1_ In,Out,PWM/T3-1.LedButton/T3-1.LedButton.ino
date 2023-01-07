#include "Led.h"
#include "Button.h"

int LED_RED = 5;
int BUTTON = 15;

Led led(LED_RED);
Button button(BUTTON);

void setup() {
}

void loop() {
  if(!button.isPressed()){
    led.red_high();
  } else {
    led.red_low();
  }
}