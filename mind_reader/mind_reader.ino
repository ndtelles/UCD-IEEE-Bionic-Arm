#include <Brain.h>
#include <Servo.h>

// Set up the brain parser, pass it the hardware serial object you want to listen on.
Brain brain(Serial);
const int numberOfServos = 5;
Servo *servos[numberOfServos];
float averageAttention = 15;
float averagePosition = 0;
float motorPosition = 0; // The current motor position
float incrementAmount = 0.30; // Controls speed which motor can move from one position to another
const float buffer = 3; // If the motor is between +buffer or -buffer dont change the position


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
    averageAttention = averageAttention * 0.4 + (attention + 15) * 0.6;

    // Limit attention to 75, which limits averagePosition to 150 
    if (averageAttention > 75) {
      averageAttention = 75;  
    }

    // Limit attention to a minimum of 15, which limits the minimum of averagePosition to 30
    if (averageAttention < 15) {
      averageAttention = 15;
    }

// So far we have seen values between 0 and 100
    averagePosition = 2 * averageAttention;
  }

// Incrementaly rotate the motor so that the fingers do not jerk around
  if (motorPosition < averagePosition - buffer) {
    motorPosition += incrementAmount;
    updateServoPositions(motorPosition);
    Serial.println(motorPosition);
    delay(10);
  }
  else if (motorPosition > averagePosition + buffer ) {
    motorPosition -= incrementAmount;
    updateServoPositions(motorPosition);
    Serial.println(motorPosition);
    delay(10);
  }

}

