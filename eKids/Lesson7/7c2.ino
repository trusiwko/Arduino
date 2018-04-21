/*
  2
9   3
  8
7   4
  6   5
*/

int d0 = B11101101;
int d1 = B01100000;
int d2 = B11001110;
int d3 = B11101010;
int d4 = B01100011;
int d5 = B10101011;
int d6 = B10101111;
int d7 = B11100000;
int d8 = B11101111;
int d9 = B11101011;

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void g1() {
  for (int j = 0; j < 8; j++) {
    digitalWrite(9-j, bitRead(d1, j));
  }
}

void g2() {
  for (int j = 0; j < 8; j++) {
    digitalWrite(9-j, bitRead(d2, j));
  }
}

void g3() {
  for (int j = 0; j < 8; j++) {
    digitalWrite(9-j, bitRead(d3, j));
  }
}

void g4() {
  for (int j = 0; j < 8; j++) {
    digitalWrite(9-j, bitRead(d4, j));
  }
}

void g5() {
  for (int j = 0; j < 8; j++) {
    digitalWrite(9-j, bitRead(d5, j));
  }
}

void g6() {
  for (int j = 0; j < 8; j++) {
    digitalWrite(9-j, bitRead(d6, j));
  }
}

void g7() {
  for (int j = 0; j < 8; j++) {
    digitalWrite(9-j, bitRead(d7, j));
  }
}

void g8() {
  for (int j = 0; j < 8; j++) {
    digitalWrite(9-j, bitRead(d8, j));
  }
}

void g9() {
  for (int j = 0; j < 8; j++) {
    digitalWrite(9-j, bitRead(d9, j));
  }
}

void g0() {
  for (int j = 0; j < 8; j++) {
    digitalWrite(9-j, bitRead(d0, j));
  }
}

void loop()
{
  for (int i = 0; i <= 9; i++) {
    if (i==0) { g0(); }
    if (i==1) { g1(); }
    if (i==2) { g2(); }
    if (i==3) { g3(); }
    if (i==4) { g4(); }
    if (i==5) { g5(); }
    if (i==6) { g6(); }
    if (i==7) { g7(); }
    if (i==8) { g8(); }
    if (i==9) { g9(); }
    delay(500);
  }
}