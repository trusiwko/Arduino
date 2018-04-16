#define RED 9
#define GREEN 11
#define BLUE 10

int speed = 5; // Скорость, с которой будет нарастать яркость
int r = 0;
int g = 0;
int b = 0;
int v;

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  // Подключим генератор случайных чисел как уловитель шумов с пина 0
  randomSeed(analogRead(0));
}

// Процедура для плавного перелива. Указываем с какого значения до какого
//  увеличивать (или уменьшать) значение на 1.
void smooth(int pin, int from, int to) {
  // Будем изменять переменную from до тех пор, пока она не станет равной переменной to
  // Сделаем копию переменной from, назовем ее c и будем работать с ней
  int c = from;
  // У нас два варианта, бежим по нарастающей от 0 до 255
  if (from < to) {
    while (c < to) {
      analogWrite(pin, c);
      c += speed;
      delay(10);
    }
  // Или бежим по убывающей от 255 до 0
  } else {
    while (c > to) {
      analogWrite(pin, c);
      c -= speed;
      delay(10);
    }
  }
  // Ждем секунду для закрепления цвета
  delay(1000 / speed);
}

void loop()
{
  // Получаем случайный цвет для красного
  v = random(256);
  smooth(RED, r, v); 
  r = v; 
  // Получаем случайный цвет для зеленого
  v = random(256);
  smooth(GREEN, g, v);
  g = v;
  // Получаем случайный цвет для синего
  v = random(256);
  smooth(BLUE, b, v);
  b = v;
}