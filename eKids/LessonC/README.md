# Датчик Холла

Датчик Холла реагирует на магнитное поле. У нас используется датчик, который реагирует только на один полюс магнита. Подключаем датчик по схеме, расположенной справа:

![img](https://github.com/trusiwko/Arduino/raw/master/eKids/LessonC/src/img1.png)

В итоге пока магнит не поднесли, будем получать `HIGH`, когда поднесем магнит, получим `LOW`.

# Джойстик

Джойстик передает на ардуино сразу две координаты - x и y. Их считываем с помощью `analogRead`. Под джойстиком расположена кнопка, которую можно нажать, нажав на сам джойстик. Таким образом джойстик имеет пять пинов: Питание (VCC или +5V), Земля (GND), два пина с которых поступает сигнал с координатами - вертикальная (VER или VRy) и горизонтальная (HOR или VRx) и пятый пин - сигнал с кнопки (SEL или SW).

![img](https://github.com/trusiwko/Arduino/raw/master/eKids/LessonC/src/18-1a.jpg)

Код [с сайта http://arduino-kit.ru/]( http://arduino-kit.ru/textpage_ws/pages_ws/proekt-18_--obrabatyivaem-dannyie-ot-djoystika.-upravlenie-pan-tilt-bracket-s-pomoschyu-djoystika):

```C++
const int axisX=A0 // ось Х подключена к A0
const int axisY=A1 // ось Y подключена к A1
const int axisZ=2 // ось Z (кнопка джойстика) подключена к D2
int valX, valY, valZ = 0; // переменные для хранения значений осей
void setup()
{
pinMode(axis_Z, INPUT_PULLUP); // конфигурируем D2 как INPUT с включением
// подтягивающего резистора внутри процессора
Serial.begin(9600);
}
void loop() {
valX = analogRead(axisX); // значение оси Х
valY = analogRead(axisY); // значение оси Y
valZ = 1-digitalRead(axisZ); // значение оси Z (кнопка)
// выводим значения в монитор
Serial.print("X:");Serial.print(valX, DEC);
Serial.print(" | Y:");Serial.print(valY, DEC)
Serial.print(" | Z: ");Serial.println(valZ, DEC);
delay(500); // пауза перед следующим считыванием данных
}
```
Данные отображаются в мониторе серийного порта.

# Датчик наклона

Датчик наклона представляет собой кнопку - когда датчик в вертикальном положении - кнопка нажата, при наклоне датчика контакты размыкаются (внутри баночки сенсора расположен металлический шарик, который замыкает/размыкает контакты).

(Datasheet)[https://www.arduino.cc/documents/datasheets/TiltSensor.PDF]

Датчик наклона также можно использовать как датчик удара. При ударе шарик начинает подпрыгивать и размыкать контакты. Это также можно легко отследить.

![img](https://github.com/trusiwko/Arduino/raw/master/eKids/LessonC/src/img2.png)