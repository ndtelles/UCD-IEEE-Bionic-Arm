#include <Brain.h>
#include <Servo.h>

// Set up the brain parser, pass it the hardware serial object you want to listen on.
Brain brain(Serial);
Servo servo1;
float average_attention = 0;
float average_position = 0;
float motor_position = 0; # The current motor position
float increment_amount = 0.15; # Controls speed which motor can move from one position to another
float buffer = 1; # If the motor is between +buffer or -buffer dont change the position

void setup() {
  // Start the hardware serial.
  Serial.begin(9600);
  servo1.attach(9);
}

void loop() {
  // Expect packets about once per second.
  // The .readCSV() function returns a string (well, char*) listing the most recent brain data, in the following format:
  // "signal strength, attention, meditation, delta, theta, low alpha, high alpha, low beta, high beta, low gamma, high gamma"
  if (brain.update()) {
    Serial.println(brain.readCSV());
    int attention = brain.readAttention();
# Take weighted average of attention with more enphasis on newer values
    average_attention = average_attention * 0.4 + attention * 0.6;

# So far we have seen values between 0 and 100 for
    average_position = 2 * average_attention;
  }

# Incrementaly rotate the motor so that the fingers do not jerk around
  if (motor_position < average_position - buffer) {
    motor_position += increment_amount;
    Serial.println(motor_position);
    delay(10);
  }
  else if (motor_position > average_position + buffer) {
    motor_position -= increment_amount;
    Serial.println(motor_position);
    delay(10);
  }
  servo1.write(motor_position);



}

