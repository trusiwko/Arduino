#define RED 9
#define GREEN 11
#define BLUE 10

int speed = 5; // Скорость, с которой будет нарастать яркость

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
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
  analogWrite(RED, 255); // Красный (включим для первого запуска)
  smooth(BLUE, 0, 255);  // Фуксия (пурпурный) (R+B)
  smooth(RED, 255, 0);   // Синий (B)
  smooth(GREEN, 0, 255); // Сине-зеленый (G+B)
  smooth(BLUE, 255, 0);  // Зеленый (G)
  smooth(RED, 0, 255);   // Желтый (R+G)
  smooth(GREEN, 255, 0); // Красный (R)
}