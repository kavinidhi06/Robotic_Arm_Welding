#include <SoftwareSerial.h>
#include <Servo.h>

// SoftwareSerial pins (RX, TX)
// Connect HC-05 TX to Pin 2, and HC-05 RX to Pin 3
SoftwareSerial BTSerial(2, 3);

Servo baseServo;      // Base rotation
Servo shoulderServo;  // Lower arm link
Servo elbowServo;     // Upper arm/welding tip

// Default neutral angles
int basePos = 90;
int shoulderPos = 90;
int elbowPos = 90;

const int stepSize = 5; // Step movement per command

void setup() {
  BTSerial.begin(9600);
  
  baseServo.attach(9);
  shoulderServo.attach(10);
  elbowServo.attach(11);

  // Set initial home positions
  baseServo.write(basePos);
  shoulderServo.write(shoulderPos);
  elbowServo.write(elbowPos);
}

void loop() {
  if (BTSerial.available()) {
    char cmd = BTSerial.read();

    // Base Servo (Left / Right)
    if (cmd == 'L' && basePos < 180) basePos += stepSize;
    else if (cmd == 'R' && basePos > 0) basePos -= stepSize;

    // Shoulder Servo (Forward / Back)
    else if (cmd == 'F' && shoulderPos < 180) shoulderPos += stepSize;
    else if (cmd == 'B' && shoulderPos > 0) shoulderPos -= stepSize;

    // Elbow / Tip Servo (Up / Down)
    else if (cmd == 'U' && elbowPos < 180) elbowPos += stepSize;
    else if (cmd == 'D' && elbowPos > 0) elbowPos -= stepSize;

    // Update positions
    baseServo.write(basePos);
    shoulderServo.write(shoulderPos);
    elbowServo.write(elbowPos);
  }
}