# Работа с фоторезистором

Фоторезистор - это такой резистор, сопротивление которого меняется в зависимости от освещения. В темноте его сопротивление большое (несколько кОм), при ярком освещении его сопротивление маленькое (несколько сотен Ом).

Когда мы работали с потенциометром, мы рассматривали его как два резистора с переменным значением, между которыми мы снимали напряжение. Такая схема называется "Делитель напряжения на резисторах". Когда мы крутили ручку потенциометра, сопротивление первого резистора увеличивалось, а второго соответственно уменьшалось. В сумме сопротивления всегда составляли номинал потенциометра (10 кОм). 

![img](https://github.com/trusiwko/Arduino/raw/master/eKids/Lesson8/src/img1.jpg)

Чем меньше сопротивление первого резистора, тем большее напряжение мы получали на выходе между резисторами.

При работе с фоторезистором второй постоянный мы возьмем самостоятельно. Номинал резистора должен быть большим, чтобы при ярком освещении, когда сопротивление фоторезистора будет стремиться к нулю, у нас не было короткого замыкания. Возьмем резистор на 10 кОм.

Выход между резисторами подключим к пину А0 для снятия показаний. Дополнительно возьмем один светодиод и подключим его через резистор 220 Ом к пину 9:

![8A](https://github.com/trusiwko/Arduino/raw/master/eKids/Lesson8/8A.jpg)

В данной схеме ток от пина 5V пойдет через фоторезистор и через резистор 10кОм в землю. Между резисторами будем брать напряжение в пин А0.

Для просмотра показаний удобно использовать серийный порт ардуино. Откроем базовый пример "AnalogReadSerial": File / Examples / 01.Basics / AnalogReadSerial.

В блоке _setup_ у нас только одна запись:

```C++
Serial.begin(9600);
```

В которой говорится, что мы устанавливаем соединение на скорости 9600 бит в секунду. Основной цикл программы содержит несколько строк. Во-первых, нам необходимо считать показания с аналогового пина A0, для этого воспользуемся функцией `analogRead`, а ее значение поместим в переменную с именем `sensorValue`:
```C++ 
int sensorValue = analogRead(A0);
```
Функция возвращает число от 0 до 1023, отправим его в серийный порт, чтобы его можно было увидеть:
```C++
Serial.println(sensorValue);
```
Ну и добавим задержку, задержку можно поставить побольше, например 500мс. После запуска программы необходимо открыть Монитор серийного порта в ардуино: Tools - Serial Monitor, или просто нажать CTRL+SHIFT+M. Внизу справа есть список с выбранной скоростью (9600 baud), необходимо убедиться что скорости в `Serial.begin` и в данном списке совпадают.

> На tinkercad монитор серийного порта открывается на вкладке "Code" кнопкой "Serial Monitor" внизу.

Теперь изменяя яркость освещения над фоторезистором мы должны наблюдать различные значения. Мы можем наблюдать, что чем темнее, тем меньшее значение показывает программа.

## Ночник

Добавим условие - если показания становятся меньше определенных, например 800, то будем включать светодиод. (Пример с серийным портом можно оставить). Полный код программы будет выглядеть так:
```C++
int v;

void setup()
{
  pinMode(A0, INPUT);
  pinMode( 9, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  v = analogRead(A0);
  if (v < 900) {
  	digitalWrite(9, HIGH);
  } else {
  	digitalWrite(9, LOW);
  }
  Serial.println(v);
  delay(300);
}
```

![8A](https://github.com/trusiwko/Arduino/raw/master/eKids/Lesson8/8A.gif)