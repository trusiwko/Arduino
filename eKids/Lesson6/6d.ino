#include <Servo.h>

int pos = 90;

Servo servo;

void setup()
{
  servo.attach(9);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  servo.write(pos);
}

void loop()
{
  if (digitalRead(10) == HIGH) {
    pos += 5;
  }
  if (digitalRead(11) == HIGH) {
    pos -= 5;
  }
  servo.write(pos);
  delay(200);
}