/*
  2
9   3
  8
7   4
  6   5
*/

int d[] = {
  B11101101,
  B01100000,
  B11001110,
  B11101010,
  B01100011,
  B10101011,
  B10101111,
  B11100000,
  B11101111,
  B11101011,
};

void setup()
{
  for (int i = 2; i<=9; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  for (int i = 0; i <= 9; i++) {
    for (int j = 0; j < 8; j++) {
      digitalWrite(9-j, bitRead(d[i], j));
    }
    delay(500);
  }
}