#include <Joystick.h>

JoyState_t joySt; // Include joySt

// If you have only one analog stick, set this to 1,
// If you have 2, set this to 2,
// If you do not have any at all, set this to 0.
// In theory, 4 are possible, but this script is limited to 2.
int AnalogSticks = 2;

// Analog stick input pins, invert, and deadzone:
int deadzone = 5; // Values under 5 will return 0
int x1Pin = A1;
int y1Pin = A0;
int x2Pin = A2;
int y2Pin = A3;
int InvertX1 = 0;
int InvertY1 = 0;
int InvertX2 = 0;
int InvertY2 = 1;

// Button input pins. Please take care not to use a value twice!:
// If you do NOT use a button listed here, please assign it to a FREE, UNSUSED pin !!THIS IS IMPORTANT!!
int PinA = 2;
int PinB = 3;
int PinX = 4;
int PinY = 5;
int PinStart = 9;
int PinSelect = 8;
int PinDPadUp = 10;
int PinDPadDown = 16;
int PinDPadLeft = 14;
int PinDPadRight = 15;
//unused
//int PinL1 = 11;
//int PinL2 = 12;
//int PinR1 = 13;
//int PinR2 = 14;

// Button mapping (1-14). Please take care not to use a value twice!:
// If you do NOT use a button in the input map, set it to 0 here.
int A = 1;
int B = 2;
int X = 3;
int Y = 4;
int Start = 5;
int Select = 6;
int DPadUp = 7;
int DPadDown = 8;
int DPadLeft = 9;
int DPadRight = 10;
//unused
//int L1 = 11;
//int L2 = 12;
//int R1 = 13;
//int R2 = 14;

// Variable declarations for analog sticks
int x1Zero, y1Zero;
int x1Value, y1Value;
int x2Zero, y2Zero;
int x2Value, y2Value;
int x1Min, x1Max;
int y1Min, y1Max;
int x2Min, x2Max;
int y2Min, y2Max;
int x1F1, x1F2;
int y1F1, y1F2;
int x2F1, x2F2;
int y2F1, y2F2;

// Array for storing button states
int PressVals[15] = {0,1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192};
int PressedVal[14];

void setup(){
  // Declare buttons as inputs
  pinMode(1, INPUT_PULLUP);
  pinMode(0, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  
  // Declare specified pins as analog inputs for analog sticks
  pinMode(x1Pin, INPUT);
  pinMode(y1Pin, INPUT);
  pinMode(x2Pin, INPUT);
  pinMode(y2Pin, INPUT);
  
  // Measure 'neutral' position for analog sticks
  x1Zero = analogRead(x1Pin);
  y1Zero = analogRead(y1Pin);
  x2Zero = analogRead(x2Pin);
  y2Zero = analogRead(y2Pin);
  joySt.xRotAxis = 0;
  joySt.yRotAxis = 0;
  joySt.xAxis = 0;
  joySt.yAxis = 0;
}
void loop(){
  // Button states are checked with digitalRead
  // For a common ground PCB, it checks for a LOW state
  // If it detects one on any button pin, it will return a corresponding
  // value counting from 1-8192 and later on these values are added together,
  // else the value is 0
  if (digitalRead(PinA) == LOW) {
    PressedVal[0] = PressVals[A];
  }
  else {
    PressedVal[0] = 0;
  }
  if (digitalRead(PinB) == LOW) {
    PressedVal[1] = PressVals[B];
  }
  else {
    PressedVal[1] = 0;
  }
  if (digitalRead(PinX) == LOW) {
    PressedVal[2] = PressVals[X];
  }
  else {
    PressedVal[2] = 0;
  }
  if (digitalRead(PinY) == LOW) {
    PressedVal[3] = PressVals[Y];
  }
  else {
    PressedVal[3] = 0;
  }
  if (digitalRead(PinStart) == LOW) {
    PressedVal[4] = PressVals[Start];
  }
  else {
    PressedVal[4] = 0;
  }
  if (digitalRead(PinSelect) == LOW) {
    PressedVal[5] = PressVals[Select];
  }
  else {
    PressedVal[5] = 0;
  }
  if (digitalRead(PinDPadUp) == LOW) {
    PressedVal[6] = PressVals[DPadUp];
  }
  else {
    PressedVal[6] = 0;
  }
  if (digitalRead(PinDPadDown) == LOW) {
    PressedVal[7] = PressVals[DPadDown];
  }
  else {
    PressedVal[7] = 0;
  }
  if (digitalRead(PinDPadLeft) == LOW) {
    PressedVal[8] = PressVals[DPadLeft];
  }
  else {
    PressedVal[8] = 0;
  }
  if (digitalRead(PinDPadRight) == LOW) {
    PressedVal[9] = PressVals[DPadRight];
  }
  else {
    PressedVal[9] = 0;
  }
/*
  if (digitalRead(PinL1) == LOW) {
    PressedVal[10] = PressVals[L1];
  } 
  else {
    PressedVal[10] = 0;
  }
  if (digitalRead(PinL2) == LOW) {
    PressedVal[11] = PressVals[L2];
  }
  else {
    PressedVal[11] = 0;
  }
  if (digitalRead(PinR1) == LOW) {
    PressedVal[12] = PressVals[R1];
  }
  else {
    PressedVal[12] = 0;
  }
  if (digitalRead(PinR2) == LOW) {
    PressedVal[13] = PressVals[R2];
  }
  else {
    PressedVal[13] = 0;
  }
*/
  // Read analog sticks and respect the deadzone value
  x1Value = analogRead(x1Pin) - x1Zero;
  y1Value = analogRead(y1Pin) - y1Zero;
  x2Value = analogRead(x2Pin) - x2Zero;
  y2Value = analogRead(y2Pin) - y2Zero;
  if(abs(x1Value) < deadzone) {
    x1Value = 0;
  }
  if(abs(y1Value) < deadzone) {
    y1Value = 0;
  }
  if(abs(x2Value) < deadzone) {
    x2Value = 0;
  }
  if(abs(y2Value) < deadzone) {
    y2Value = 0;
  }

  // Autocalibration of analog sticks (by Helder + wermy)
  if (x1Value > 0 && x1Value > x1Max) {
    x1Max = x1Value;
  } else if (x1Value < 0 && x1Value < x1Min) {
    x1Min = x1Value;
  }

  if (y1Value > 0 && y1Value > y1Max) {
    y1Max = y1Value;
  } else if (y1Value < 0 && y1Value < y1Min) {
    y1Min = y1Value;
  }

  float x1sMax = abs(x1Max);
  if (x1Value < 0) {
    x1sMax = abs(x1Min);
  }

  float y1sMax = abs(y1Max);
  if (y1Value < 0) {
    y1sMax = abs(y1Min);
  }
  
  if (x2Value > 0 && x2Value > x2Max) {
    x2Max = x2Value;
  } else if (x2Value < 0 && x2Value < x2Min) {
    x2Min = x2Value;
  }

  if (y2Value > 0 && y2Value > y2Max) {
    y2Max = y2Value;
  } else if (y2Value < 0 && y2Value < y2Min) {
    y2Min = y2Value;
  }

  float x2sMax = abs(x2Max);
  if (x2Value < 0) {
    x2sMax = abs(x2Min);
  }

  float y2sMax = abs(y2Max);
  if (y2Value < 0) {
    y2sMax = abs(y2Min);
  }
  int16_t x1Final = (((float)x1Value / x1sMax)*127);
  int16_t y1Final = (((float)y1Value / y1sMax)*127);
  int16_t x2Final = (((float)x2Value / x2sMax)*127);
  int16_t y2Final = (((float)y2Value / y2sMax)*127);

  // Check if Axes need to be inverted, and if yes, do so
  if (InvertX1 == 0) {
    x1F1 = 127;
    x1F2 = -127;
  }
  else {
    x1F1 = -127;
    x1F2 = 127;
  }
  if (InvertY1 == 0) {
    y1F1 = 127;
    y1F2 = -127;
  }
  else {
    y1F1 = -127;
    y1F2 = 127;
  }
  if (InvertX2 == 0) {
    x2F1 = 127;
    x2F2 = -127;
  }
  else {
    x2F1 = -127;
    x2F2 = 127;
  }
  if (InvertY2 == 0) {
    y2F1 = 127;
    y2F2 = -127;
  }
  else {
    y2F1 = -127;
    y2F2 = 127;
  }
  
  // Check how many analog sticks have been specified (0, 1, 2)
  // and disable (center) any that aren't used.
  if (AnalogSticks != 1 && AnalogSticks != 2) {
    x1Final = 0;
    y1Final = 0;
    x2Final = 0;
    y2Final = 0;
  }
  if (AnalogSticks == 1) {
    x1Final = 0;
    y1Final = 0;
  }
  
  // Parse autocalibrated analog stick values
  joySt.xRotAxis = map(x1Final, x1F1, x1F2, 0, 255);
  joySt.yRotAxis = map(y1Final, y1F1, y1F2, 0, 255);
  joySt.xAxis = map(x2Final, x2F1, x2F2, 0, 255);
  joySt.yAxis = map(y2Final, y2F1, y2F2, 0, 255);
      
  // Combine the button states together and parse them as one value to joySt.buttons
  joySt.buttons = PressedVal[0] + PressedVal[1] + PressedVal[2] + PressedVal[3] + PressedVal[4] + PressedVal[5] + PressedVal[6] + PressedVal[7] + PressedVal[8] + PressedVal[9] + PressedVal[10] + PressedVal[11] + PressedVal[12] + PressedVal[13];

  // We don't have a throttle, rudder, or hat switches, so set them to 0  
  joySt.throttle = 0;
  joySt.rudder = 0;
  joySt.hatSw1 = 0;
  joySt.hatSw2 = 0;

  // Send everything to USB
  Joystick.setState(&joySt);
}
