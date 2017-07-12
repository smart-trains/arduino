const int RO = 8; // Receiver Output
const int RE = 7; // Receiver output Enable, active LOW
const int DE = 6; // Driver output Enable, active HIGH
const int DI = 5; // Driver Input

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RO, INPUT_PULLUP);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  digitalWrite(RE, LOW);
  digitalWrite(DE, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(Serial.read());
}
