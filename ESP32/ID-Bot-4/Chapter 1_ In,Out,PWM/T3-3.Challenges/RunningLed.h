class Running {

private:
  int _yellow;
  int _blue;
  int _red;

public:
  Running(int yellowLed, int blueLed, int redLed){
    _yellow = yellowLed;
    _blue = blueLed;
    _red = redLed;

    pinMode(_yellow, OUTPUT);
    pinMode(_blue, OUTPUT);
    pinMode(_red, OUTPUT);
  }

  void yellow(){
    digitalWrite(_yellow, HIGH);
    digitalWrite(_blue, LOW);
    digitalWrite(_red, LOW);
  }

  void blue(){
    digitalWrite(_yellow, LOW);
    digitalWrite(_blue, HIGH);
    digitalWrite(_red, LOW);
  }

  void red(){
    digitalWrite(_yellow, LOW);
    digitalWrite(_blue, LOW);
    digitalWrite(_red, HIGH);
  }

  void off(){
    digitalWrite(_yellow, LOW);
    digitalWrite(_blue, LOW);
    digitalWrite(_red, LOW);
  }

};