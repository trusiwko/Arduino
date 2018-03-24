// Вместо цифр 8,9,10 будем использовать названия
#define RED 8
#define YELLOW 9
#define GREEN 10

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop()
{
  // Включаем красный светодиод и ждем 6 секунд
  digitalWrite(RED, HIGH);
  delay(6000);
  // Включаем желтый светодиод на 2 секунды
  digitalWrite(YELLOW, HIGH);
  delay(2000);
  // Выключаем красынй и желтый, включаем зеленый на 5 секунд
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, HIGH);
  delay(5000);
  // Мигаем зеленым - выключаем на полсекунды, включаем на
  // полсекунды, повторяем 4 раза
  digitalWrite(GREEN, LOW);
  delay(500);
  digitalWrite(GREEN, HIGH);
  delay(500);
  digitalWrite(GREEN, LOW);
  delay(500);
  digitalWrite(GREEN, HIGH);
  delay(500);
  digitalWrite(GREEN, LOW);
  delay(500);
  digitalWrite(GREEN, HIGH);
  delay(500);
  digitalWrite(GREEN, LOW);
  delay(500);
  // Включаем желтый на 2 секунды
  digitalWrite(YELLOW, HIGH);
  delay(2000);
  // Выключаем желтый, цикл повторяется
  digitalWrite(YELLOW, LOW);
}