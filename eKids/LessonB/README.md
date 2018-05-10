# Работа с ЖК-дисплеями

Жидкокристаллические дисплеи (LCD) используются для вывода текста. Стандартные дисплеи имеют разрешение 16 символов в столбец и 2 строки.

> На tinkercad в группе Starters/Arduino можно найти пример LCD: 
![LCD](https://github.com/trusiwko/Arduino/raw/master/eKids/LessonB/src/img1.png)

![img](https://github.com/trusiwko/Arduino/raw/master/eKids/LessonB/src/img2.png)

У нас используется два типа дисплеев: 1602A (с синим фоном и белыми буквами) и MT-16S2H (с зеленым фоном и черными буквами). Количество ног у них совпадает, но есть одно существенное различие - у 1602A ноги расположены так, как на картинке выше, а у MT-16S2H они внизу и в таком порядке: 14,13,12,11,10,9,8,7,6,5,4,3,2,1,16,15. Т.е. ноги слева направо идут с 14 по 1, а затем последние две 16 и 15. На плате возле ног нарисованы числа 14, 1 и 15. Поэтому подключать такой дисплей нужно аккуратно. Можно его перевернуть и переставить крайние два провода например:

![img](https://github.com/trusiwko/Arduino/raw/master/eKids/LessonB/src/img3.png)

Код предложенный на tinkercad:

```C++
/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
```

Состоит из пары строк. Первая строка - подключение библиотеки `LiquidCrystal.h`. Далее создается переменная, которая сразу инициализируется пинами: 
```C++
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
```
В блоке установки указываем, какой LCD у нас подключен - 16х2. И выводим сообщение в первую строку.

В основном цикле программы выводим некое число во вторую строку (строки начинаются с 0). Это число - количество прошедших с момента запуска скетча секунд (миллисекунды / 1000).

LCD сохраняет текст, для очистки необходимо вызывать метод `clear()`:
```C++
lcd.clear();
```

Экран MT-16S2H также может выводить русские символы, для этого их необходимо указывать в шестнадцатеричном формате в последовательности `\x##`. Что именно указывать можно посмотреть в таблице 5 на стр. 8 документации (первым идет столбец, затем строка): http://files.amperka.ru/datasheets/MT-16S2H.pdf 

Например, буква `П` находится на пересечении столбца А и строки 8, поэтому для вывода `П` мы напишем `\xA8`, буквы `р` (на первой страницы нет), но есть буква `p` (латинская), которая расположена на пересечении 7 и 0, для нее будет код \x70 (а вообще можно и просто указать латинскую букву без всякого кода, просто p). Слово "Привет" в итоге будет выглядеть так:
```C++
lcd.print("\xA8\x70\xB8\xB3\x65\xBF");
```
Или так:
```C++
// Буквы p,e выводятся латинскими:
lcd.print("\xA8p\xB8\xB3""e\xBF");
```
Тут обратите внимание на две кавычки перед e, это нужно для того, чтобы ардуино воспринял символ `xB3`, как отдельный, а не `xB3e...`. Т.е. мы разбили строку на две. Почему две кавычки мы не поставили перед `p`? Потому что ардуино воспринимает как продолжение только символы шестнадцатеричные: `a`,`b`,`c`,`d`,`e`,`f`.