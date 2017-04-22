#include <Servo.h>

Servo pinky, ringF, middleF, indexF, thumb;
int bend = 800, straight = 2200, half = 1800, wait = 500, pbend = 2200, pstraight = 800, phalf = 1300;

enum Commands 
{
  G1_TEST = 84,// T
  G1_PINCH = 112, // p
  G1_GRAB = 103, // g
  G1_ROCK = 114, // r
  G1_GNARLY = 52,
  G1_POINT = 80, // P
  G1_PEACE = 6,
  G1_FLICK = 7,
  G1_NEUTRAL = 110, // n
  G1_TYPE = 9,
  G1_RELAX = 10,
  G1_MOUSE = 11,
  G1_WAVE = 119, // wave
  G1_THUMBS_UP = 16, // t
  G1_PENCIL = 14,
};

void setup() {
  // put your setup code here, to run once:
  pinky.attach(13);
  ringF.attach(12);
  middleF.attach(11);
  indexF.attach(10);
  thumb.attach(9);
//  neutral();
  delay(500);


  Serial.begin(9600);
}

void test()
{
  Serial.println("HERE");
  drive(pinky, pbend);
  drive(pinky, pstraight);
  drive(ringF, bend);
  drive(ringF, straight);
  drive(middleF, straight); // i
  drive(middleF, bend); // i
  drive(indexF, straight); // i
  drive(indexF, bend); // i
  drive(thumb, bend);
  drive(thumb, straight);
}

void pinch()
{
  qDrive(thumb, bend);
  qDrive(ringF, straight);
  qDrive(middleF, bend); // i
  qDrive(pinky, pstraight);
  delay(200);
  qDrive(indexF, straight); // i
}

void grab()
{
  qDrive(indexF, straight); // i
  qDrive(thumb, bend);
  qDrive(ringF, bend);
  qDrive(middleF, straight); // i
  qDrive(pinky, pbend);
}

void rock()
{
  qDrive(middleF, straight); // i
  delay(200);
  qDrive(indexF, bend); // i
  qDrive(thumb, straight);
  qDrive(ringF, bend);
  qDrive(pinky, pstraight);
}

void gnarly()
{
  qDrive(middleF, straight); // i
  delay(200);
  qDrive(indexF, straight); // i
  qDrive(thumb, straight);
  qDrive(ringF, bend);
  qDrive(pinky, pstraight);
}

void point()
{
  qDrive(indexF, bend); // i
  qDrive(thumb, bend);
  qDrive(ringF, bend);
  qDrive(middleF, straight); // i
  qDrive(pinky, pbend);
}

void peace()
{
  qDrive(indexF, bend); // i
  qDrive(thumb, bend);
  qDrive(ringF, bend);
  qDrive(middleF, bend); // i
  qDrive(pinky, pbend);
}

void flick()
{
  qDrive(indexF, straight); // i
  qDrive(thumb, bend);
  qDrive(ringF, bend);
  qDrive(middleF, bend); // i
  qDrive(pinky, pbend);
}

void neutral()
{
  qDrive(indexF, bend); // i
  qDrive(thumb, straight);
  qDrive(ringF, straight);
  qDrive(middleF, bend); //i
  qDrive(pinky, pstraight);
}

void type()
{
  qDrive(thumb, half);
  qDrive(pinky, phalf);
  qDrive(indexF, half);
  qDrive(middleF, half);
  qDrive(ringF, half);
}

void mouse()
{
  qDrive(thumb, bend);
  qDrive(pinky, pbend);
  qDrive(indexF, straight); // i
  qDrive(middleF, bend); // i
  qDrive(ringF, straight);
}

void wave()
{
  for(int i = 0; i < 3; i++)
  {
    qDrive(middleF, straight); // i
    delay(200);
    qDrive(thumb, straight);
    qDrive(pinky, pbend);
    qDrive(indexF, straight); //i
    qDrive(ringF, bend);
    delay(500);
    neutral();
    delay(500);
  }
}

void thumbsup()
{
    qDrive(middleF, straight); // i
    delay(200);
    qDrive(thumb, straight);
    qDrive(pinky, pbend);
    qDrive(indexF, straight); // i
    qDrive(ringF, bend);
}

void pencil()
{
  qDrive(middleF, straight); // i
  delay(200);
  qDrive(thumb, bend);
  qDrive(pinky, pbend);
  qDrive(ringF, bend);
  delay(500);
  qDrive(indexF, straight); // i
}
void drive(Servo s, int pos)
{
  s.writeMicroseconds(pos);
  delay(wait);
}

void qDrive(Servo s, int pos)
{
  s.writeMicroseconds(pos);
}

void loop() {
  // put your main code here, to run repeatedly:
//  if (Serial.available() > 0) {
//    Serial.println("Here");
//    int inchar = Serial.read();
//    Serial.println(inchar);
////    neutral();
////    delay(20);
//    action(inchar);
//  }
//  action(84); // test
//  action(119); // wave
}

void action(int command)
{
      switch (command)
      {
        Serial.println("here");
      case G1_TEST:
        Serial.println("test");
        test();
        break;
      case G1_PINCH:
        Serial.println("pinch");
        pinch();
        break;
      case G1_GRAB:
        Serial.println("grab");
        grab();
        break;
      case G1_ROCK:
        Serial.println("rock");
        rock();
        break;
      case G1_GNARLY:
        Serial.println("gnarly");
        gnarly();
        break;
      case G1_POINT:
        point();
        break;
      case G1_PEACE:
        peace();
        break;
      case G1_FLICK:
        flick();
        break;
      case G1_NEUTRAL:
        Serial.println("neutral");
        neutral();
        break;
      case G1_TYPE:
        type();
        break;
      case G1_RELAX:
        neutral();
        break;
      case G1_MOUSE:
        mouse();
        break;
      case G1_WAVE:
        wave();
        break;
      case G1_THUMBS_UP:
        thumbsup();
        break;
      case G1_PENCIL:
        pencil();
        break;
      }
}
