class Led {

private:
  int _redLED;

public:
  Led(int redLED) {
    _redLED = redLED;

     pinMode(_redLED, OUTPUT);   
  }

  void red_high() {
    digitalWrite(_redLED, HIGH);
  }


  void red_low() {
    digitalWrite(_redLED, LOW);
  }

};