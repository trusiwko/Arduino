#include <Servo.h>

int pos = 0;
int p;

Servo servo_9;

void setup()
{
  servo_9.attach(9);
  pinMode(A0, INPUT);
  pinMode(10, OUTPUT);
}

void loop()
{
  p = analogRead(A0);
  pos = map(p, 0, 1023, 0, 180);
  servo_9.write(pos);
  if (p > 973 or p < 50) {
    digitalWrite(10, HIGH);
  } else {
    digitalWrite(10, LOW);
  }
  delay(100);
}