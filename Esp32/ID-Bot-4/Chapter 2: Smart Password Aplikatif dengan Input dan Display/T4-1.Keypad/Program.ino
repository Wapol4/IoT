#include <Keypad.h>
const int BARIS = 4;
const int KOLOM = 4;
char keys[BARIS][KOLOM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[BARIS] = {22, 21, 19, 18};//connect to the row pinouts of the keypad
byte colPins[KOLOM] =  {5, 4, 2, 15};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, BARIS, KOLOM);
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
}

void loop() {
char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key);
  }
}