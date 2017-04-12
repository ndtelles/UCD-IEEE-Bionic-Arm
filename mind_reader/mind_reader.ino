#include <Brain.h>
#include <Servo.h>

// Set up the brain parser, pass it the hardware serial object you want to listen on.
Brain brain(Serial);
const int numberOfServos = 5;
Servo *servos[numberOfServos];
float averageAttention = 0;
float averagePosition = 0;
float motorPosition = 0; // The current motor position
float incrementAmount = 0.15; // Controls speed which motor can move from one position to another
const float buffer = 1; // If the motor is between +buffer or -buffer dont change the position


void setup() {
  // Start the hardware serial.
  int pins[5] = {9, 10, 11, 12, 13};
  Serial.begin(9600);
  for (int i=0; i < numberOfServos; ++i) {
    Serial.println(averageAttention);
    servos[i] = new Servo();
    servos[i]->attach(pins[i]);
  }
}

void updateServoPositions(float position) {
  for (int i=0; i < numberOfServos; ++i) {
    servos[i]->write(position);
  }
}

void loop() {
  // Expect packets about once per second.
  // The .readCSV() function returns a string (well, char*) listing the most recent brain data, in the following format:
  // "signal strength, attention, meditation, delta, theta, low alpha, high alpha, low beta, high beta, low gamma, high gamma"
  if (brain.update()) {
    Serial.println(brain.readCSV());
    int attention = brain.readAttention();
// Take weighted average of attention with more enphasis on newer values
    averageAttention = averageAttention * 0.4 + attention * 0.6;

// So far we have seen values between 0 and 100
    averagePosition = 2 * averageAttention;
  }

// Incrementaly rotate the motor so that the fingers do not jerk around
  if (motorPosition < averagePosition - buffer) {
    motorPosition += incrementAmount;
    Serial.println(motorPosition);
    delay(10);
  }
  else if (motorPosition > averagePosition + buffer) {
    motorPosition -= incrementAmount;
    Serial.println(motorPosition);
    delay(10);
  }

  updateServoPositions(motorPosition);
}

