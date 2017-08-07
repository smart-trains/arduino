/*
 * Testing device for data collecting terminal (DCT)
 * based on Arduino
 * Arthor: Zhanhuai Huang
 */

/*
 * Library imports
 */
#include <Wire.h>
#include <GridEye.h>

/*
 * Physical Constants
 */
#define GRID_SIDE 8
#define NUM_CELLS GRID_SIDE*GRID_SIDE
#define ENV_TEMP_PER_UNIT GridEye_ThermistorTemp_Unit
#define GRID_TEMP_PER_UNIT GridEye_PixelOut_Unit

/*
 * Program constants
 */
const byte ADDR = 0b0001;
const byte SLAVE = 0b0101;
const byte SLAVE_RESP = 0b0100;

const int MSG_SIGN_INDEX = 0;
const int MSG_ENV_INDEX = 1;
const int MSG_GRID_INDEX = 2;

/*
 * Function heads
 */
void genMsg(byte msg[]);
bool isCalled(byte ctrl);

/*
 * Global variables
 */
GridEye e;
int grid_lv[NUM_CELLS] = {0};

/*
 * Body
 */
void setup() {
  // Initiates I2C interface (SDA = A4/upper, SCL = A5/lower)
  Wire.begin();
  // Initiates UART interface (TX = 1/upper, RX = 0/lower)
  Serial.begin(38400);

  // Sensor initiating
  e.initialReset();
  e.setFramerate(10);
}

void loop() {
  // Signature + env temp + 64*cell
  byte msg[1+1+NUM_CELLS] = {0};
  genMsg(msg);
  
  while (Serial.available() > 0) {
    byte ctrl = Serial.read();
    if (isCalled(ctrl)) {
      // Number called, send message
      Serial.write(msg, sizeof(msg));

      // Wait for next polling
      // Interval between fetching \approx 83.3ms
      delay(50);
    }
  }
}

/*
 * Self-defined functions
 */
void genMsg(byte msg[]) {
  // Construct message
  msg[MSG_SIGN_INDEX] = (SLAVE_RESP << 4) + ADDR;
  msg[MSG_ENV_INDEX] = (byte) e.thermistorTemp();
  
  e.pixelOut(grid_lv);
  for (int i = 0; i < NUM_CELLS; i++) {
    msg[MSG_GRID_INDEX + i] = (byte) grid_lv[i];
  }
}
 
bool isCalled(byte ctrl) {
  return ctrl == (SLAVE << 4) + ADDR;
}

