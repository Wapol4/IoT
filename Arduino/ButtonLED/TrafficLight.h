class TrafficLight {

  int _greenLED;
  int _yellowLED;
  int _redLED;

public:
  TrafficLight(int greenLED, int yellowLED, int redLED) {
    _greenLED = greenLED;
    _yellowLED = yellowLED;
    _redLED = redLED;

     pinMode(_greenLED, OUTPUT);
     pinMode(_yellowLED, OUTPUT);
     pinMode(_redLED, OUTPUT);   
  }

  void green() {
    digitalWrite(_greenLED, HIGH);
    digitalWrite(_yellowLED, LOW);
    digitalWrite(_redLED, LOW);
  }

  void yellow() {
    digitalWrite(_greenLED, LOW);
    digitalWrite(_yellowLED, HIGH);
    digitalWrite(_redLED, LOW);
  }

  void red() {
    digitalWrite(_greenLED, LOW);
    digitalWrite(_yellowLED, LOW);
    digitalWrite(_redLED, HIGH);
  }

  void off() {
    digitalWrite(_greenLED, LOW);
    digitalWrite(_yellowLED, LOW);
    digitalWrite(_redLED, LOW);
  }

};