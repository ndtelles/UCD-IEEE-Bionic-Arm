/*
 * This sketch's purpose is to demonstrate how reading from serial works.
 * If the muse_osc_server is running on the connected computer, the LED on
 * the arduion will turn on whenever a "1" is received over the serial line.
 * The led turning on represents that the person wearing the headset is
 * clenching their jaw
 */
#include <Servo.h>

// how much serial data we expect before a newline
const unsigned int MAX_INPUT = 50;
Servo pinky, ring, middle, index, thumb;

void setup (){
  Serial.begin (9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinky.attach(9);  // attaches the servo on pin 9 to the servo object
  ring.attach(10);
  middle.attach(11);
  index.attach(12);
  thumb.attach(13);
}

// process incoming serial data after a terminator received
void process_data (const char * data)
{
  if (atoi(data) == 1) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    grab();
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    release();
  }
}

void processIncomingByte (const byte inByte)
{
  static char input_line [MAX_INPUT];
  static unsigned int input_pos = 0;

  switch (inByte)
  {

    case '\n':   // end of text
     input_line [input_pos] = 0;  // terminating null byte

     // terminator reached! process input_line here ...
     process_data (input_line);

     // reset buffer for next time
     input_pos = 0;  
     break;
    case '\r':   // discard carriage return
      break;

    default:
      // keep adding if not full ... allow for terminating null byte
      if (input_pos < (MAX_INPUT - 1))
      input_line [input_pos++] = inByte;
      break;

  }
}

void loop()
{
  // if serial data available, process it
  while (Serial.available () > 0){
    processIncomingByte (Serial.read ());
  }  
}

void grab()
{
  pinky.write(180);
  ring.write(180);
  middle.write(180);
  index.write(180);
  thumb.write(180);
}

void release()
{
  pinky.write(0);
  ring.write(0);
  middle.write(0);
  index.write(0);
  thumb.write(0);
}
