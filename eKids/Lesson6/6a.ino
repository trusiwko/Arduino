#include <Servo.h> // Подключаем библиотеку для работы с сервоприводом 
int pos = 0;
Servo servo_9; // Переменная для управления сервоприводом
void setup()
{
  servo_9.attach(9); // Говорим к какому пину присоединен сервопривод
}

void loop()
{
  for (pos = 0; pos <= 180; pos += 1) {
    servo_9.write(pos); // Отправляем на сервопривод текущую позицию
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    servo_9.write(pos);
    delay(15);
  }
}