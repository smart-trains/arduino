const byte addr = 0b0001;
const byte slave = 0b0101;

void isCalled(void);

const int RE = 7; // Receiver output Enable, active LOW
const int DE = 6; // Driver output Enable, active HIGH

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    byte ctrl = Serial.read();
    if(isCalled(ctrl)) {
      Serial.write("cao ni ma");
    } else {
      while(Serial.available() > 0) {
        Serial.read();
      }
    }
  }
}

void isCalled(byte ctrl) {
  return ctrl == addr + (slave << 4);
}

