class Button {

private:
  int _buttonPin;

public:
  Button(int buttonPin) {
    _buttonPin = buttonPin;
    pinMode(_buttonPin, INPUT);
  }

  bool isPressed() {
    return !digitalRead(_buttonPin);
  }
  
};