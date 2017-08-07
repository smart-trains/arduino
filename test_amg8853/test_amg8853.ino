#include <Wire.h>
#include <GridEye.h>

#define GRID_SIDE 8
#define NUM_CELLS GRID_SIDE*GRID_SIDE
#define ENV_TEMP_PER_UNIT GridEye_ThermistorTemp_Unit
#define GRID_TEMP_PER_UNIT GridEye_PixelOut_Unit

GridEye e;

int grid[NUM_CELLS] = {0};

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(38400);

  e.initialReset();
  e.setFramerate(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = e.thermistorTemp() * ENV_TEMP_PER_UNIT;
  Serial.print("Env temp: ");
  Serial.println(temp);

  e.pixelOut(grid);
  Serial.println("Grid reading: ");

  for (int i = 0; i < NUM_CELLS; i++) {
    if (i && ((i % 8) == 0)) {
      Serial.println();
    }
    Serial.print(grid[i] * GRID_TEMP_PER_UNIT);
    Serial.print(' ');
  }

  Serial.println();

  delay(100);
}
