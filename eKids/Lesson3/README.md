# Проект Светофор.

Поочередно зажигаем три светодиода. Светодиоды катодами подключены к общей шине с землей, анодами через резисторы от 150 Ом (обычно это 220 Ом) к пинам 8,9 и 10.

Поняли зачем нужно писать #define вместо того, чтобы везде указывать числа 8, 9 или 10.

Также познакомились с символом ~ и с помощью пинов с указанным символом зажигали светодиоды не на полную мощность. 
Для этого вместо digitalWrite используем функцию analogWrite и передаем вторым параметром число от 0 до 255 (максимальная мощность):

```C++
analogWrite(RED, 100);
```

![Demo](https://github.com/trusiwko/Arduino/raw/master/eKids/Lesson3/demo.gif)
