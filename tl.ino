int RED = 5;
int YELLOW = 2;
int GREEN = 6;
int GREEFLASH = 3;

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

int cur = 0;
bool gflash = false;
int cdigit = 0;

byte signs[10] = {B10110111, B00100100, B10011110, B00111110, B00101101, B00111011, B10111011, B00100110, B10111111, B00111111};

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
}

void loop() {
  if (cur == 0) {
    // Включаем красный свет
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    cdigit = RED;
  }
  if (cur == RED) {
    // Переключаем его на желтый
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
  }
  if (cur == RED + YELLOW) {
    // Переключаем его на зеленый
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    cdigit = GREEN + GREEFLASH;
  }
  if (cur >= RED + YELLOW + GREEN && cur < RED + YELLOW + GREEN + GREEFLASH) {
    // Мигаем зеленым светом
    if (gflash) {
      digitalWrite(5, LOW);
      gflash = false;
    } else {
      digitalWrite(5, HIGH);
      gflash = true;
    }
  }
  if (cur == RED + YELLOW + GREEN + GREEFLASH) {
    // Переключаем на желтый свет
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
  }
  if (cur == RED + YELLOW + GREEN + GREEFLASH + YELLOW) {
    cur = -1;
  }
  cur++;

  if (cdigit >= 0) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, signs[cdigit]);
    digitalWrite(latchPin, HIGH);
  } else {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, 0);
    digitalWrite(latchPin, HIGH);
  }
  cdigit--;

  delay(1000);

}
