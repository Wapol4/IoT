#include "RunningLed.h";
#include "Button.h";

int LED_YELLOW = 5;
int LED_BLUE = 18;
int LED_RED = 19;
int BUTTON = 15;

Running run(LED_YELLOW, LED_BLUE, LED_RED);
Button button(BUTTON);

void setup()
{
  
}

void loop(){
 if(!button.isPressed()){
    run.yellow();
    delay(500);
    run.blue();
    delay(500);
    run.red();
    delay(500);
  } else {
    run.off();
  }
}