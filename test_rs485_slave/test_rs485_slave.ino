#include <Wire.h>
#include <math.h>
#include <SparkFunHTU21D.h>

HTU21D h;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);

  h.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  float humd = h.readHumidity();
  float temp = h.readTemperature();

  int humd_int = 

  Serial.println(b);
  delay(1000);
}
