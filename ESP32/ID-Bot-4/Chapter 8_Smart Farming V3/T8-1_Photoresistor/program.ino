
const float GAMMA = 0.7;
const float RL10 = 50;

void setup() {
  Serial.begin(115200);
  pinMode(15, OUTPUT);
}

void loop() {
  int analogValue = analogRead(34);
  float voltage = analogValue * 5/4095.0;
  float resistance = 2000 * voltage / (1 - voltage / 5);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
  Serial.print("Lux: ");
  Serial.println(lux);

  if (lux >= 50){
    Serial.print("Status: ");
    Serial.println("Terang");
    digitalWrite(15, HIGH);
  } else {
    Serial.print("Status: ");
    Serial.println("Gelap");
    digitalWrite(15, LOW);
  }
  delay(100);
}
