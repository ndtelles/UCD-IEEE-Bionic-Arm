/*
 * This sketch's purpose is to demonstrate how reading from serial works.
 * If the muse_osc_server is running on the connected computer, the LED on
 * the arduion will turn on whenever a "1" is received over the serial line.
 * The led turning on represents that the person wearing the headset is
 * clenching their jaw
 */


// how much serial data we expect before a newline
const unsigned int MAX_INPUT = 50;

void setup (){
  Serial.begin (9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

// process incoming serial data after a terminator received
void process_data (const char * data)
{
  if (atoi(data) == 1) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
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
