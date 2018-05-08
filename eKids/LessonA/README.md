# Считыватель RFID-карт

Для считывания RFID-карт типа Mifare Classic используется компонент RFID-RC552

![img](https://github.com/trusiwko/Arduino/raw/master/eKids/LessonA/src/img1.png)

Компонент имеет 7 выводов, из которых мы будем использовать шесть. Подключать их к ардуино следует так, как на картинке выше. Для работы со считывателем карт необходимо загрузить библиотеку `MFRC522.h`: https://www.arduinolibraries.info/libraries/mfrc522

Последняя версия на текущий момент: [MFRC522-1.4.0.zip](http://downloads.arduino.cc/libraries/github.com/miguelbalboa/MFRC522-1.4.0.zip)

После загрузки архива его необходимо распаковать и полученную папку MFRC522-1.4.0 необходимо перенести в папку с библиотеками ардуино (C:\Program Files (x86)\Arduino\libraries)

Далее в ардуино необходимо выбрать пример Examples / MFRC522 / ReadNUID и загрузить его в ардуино.

После прикладывания карты к считывателю, в мониторе серийного порта будет отображаться ее серийный номер, который в дальнейшем можно использовать в своем коде.

Исходный код:

```C++
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];

void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}
 
void loop() {

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  }
  else Serial.println(F("Card read previously."));

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}


/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
```

## Добавим пару светодиодов

Добавим два светодиода - красный (подключим к пину 7) и зеленый (подключим к пину 6). Не забываем про резисторы на 220 Ом. Запрограммируем одну из карт. Когда ее поднесем к считывателю - загорится зеленый на пару секунд. Если карта чужая - зажигаем красный.

В существующем коде исправим процедуру `printHex` которая выводит в монитор серийного порта уникальный идентификатор карты. Сделаем из процедуры функцию `getHex` с теми же параметрами, которая возвращает идентификатор в строке. И в двух местах программы, где вызывается процедура:
```C++
printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
...
printHex(rfid.uid.uidByte, rfid.uid.size);
```

Сделаем вызов новой функции и вывод ее значения в монитор серийного порта:
```C++
Serial.print(getHex(key.keyByte, MFRC522::MF_KEY_SIZE));
...
Serial.print(getHex(rfid.uid.uidByte, rfid.uid.size));
```

Код функции вместо процедуры `printHex`: 
```C++
String getHex(byte *buffer, byte bufferSize) {
  String s;
  for (byte i = 0; i < bufferSize; i++) {
    s += buffer[i] < 0x10 ? " 0" : " ";
    s += String(buffer[i], HEX);
  }
  return s;
}
```

Обратите внимание, вместо слова `void`, которое означает что процедура ничего не возвращает, мы указали `String`, что означает - что функция возвращает строку.

После запуска скетча в мониторе серийного порта изменений не будет. После того, как мы поднесем к считывателю карту - мы увидим ее уникальный номер (начинающийся с пробела, так работает наша функция). Запишем уникальный номер одной из карт, например: " 55 46 2f 50".
Теперь мы можем сравнивать результат возврата `getHex(rfid.uid.uidByte, rfid.uid.size)` с записанным ранее значением уникального номера карточки. Добавим в код условие:

```C++
  if (getHex(rfid.uid.uidByte, rfid.uid.size) == " 55 46 2f 50") {
    digitalWrite(6, HIGH);
    delay(2000);
    digitalWrite(6, LOW);
  } else {
    digitalWrite(7, HIGH);
    delay(2000);
    digitalWrite(7, LOW);
  }
```

Полный код:

```C++
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];

void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  Serial.print(getHex(key.keyByte, MFRC522::MF_KEY_SIZE));
}
 
void loop() {

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    Serial.print(getHex(rfid.uid.uidByte, rfid.uid.size));
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  }
  else Serial.println(F("Card read previously."));

  if (getHex(rfid.uid.uidByte, rfid.uid.size) == " 55 46 2f 50") {
    digitalWrite(6, HIGH);
    delay(2000);
    digitalWrite(6, LOW);
  } else {
    digitalWrite(7, HIGH);
    delay(2000);
    digitalWrite(7, LOW);
  }

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}


/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
String getHex(byte *buffer, byte bufferSize) {
  String s;
  for (byte i = 0; i < bufferSize; i++) {
    s += buffer[i] < 0x10 ? " 0" : " ";
    s += String(buffer[i], HEX);
  }
  return s;
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
```
![img](https://github.com/trusiwko/Arduino/raw/master/eKids/LessonA/AB.png)