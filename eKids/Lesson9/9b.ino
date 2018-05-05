#include "IRremote.h"

IRrecv irrecv(11); // указываем вывод, к которому подключен приемник

decode_results results;

void setup() {
  Serial.begin(9600); // выставляем скорость COM порта
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  irrecv.enableIRIn(); // запускаем прием
}

void loop() {
  if ( irrecv.decode( &results )) { // если данные пришли
    Serial.println( results.value, HEX ); // печатаем данные
    if (results.value == 0xFD30CF) {
      // Нажата кнопка 0, гасим оба светодиода
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
    }
    if (results.value == 0xFD08F7) {
      // Нажата кнопка 1, зажигаем красный:
      digitalWrite(8, HIGH);
    }
    if (results.value == 0xFD8877) {
      // Нажата кнопка 2, зажигаем зеленый:
      digitalWrite(9, HIGH);
    }
    
    irrecv.resume(); // принимаем следующую команду
  }
}