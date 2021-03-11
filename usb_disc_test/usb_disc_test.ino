/**
 * STM32F1 USB Test
 * 
 * Эксперимент с резистором 1.5к на линии данных USB
 * 
 * Подробно в этом видео https://youtu.be/U3Gb2WvjPOI
 * 
 ** Ядро для поддержки плат STM32 от rogerclarkmelbourne https://github.com/rogerclarkmelbourne/Arduino_STM32
 ** Для его работы нужно:
 *** Установить "Arduino SAM boards (Cortex-M3)" через менеджер плат
 *** Скопировать содержимое скаченного архива в папку "hardware" по пути C:\Users\[Имя пользователя]\Documents\Arduino
 *** Если папки "hardware" нет, ее нужно создать самостоятельно
 * 
 * Настройки платы:
 ** Из файла add_boards.txt (в папке со скетчем) скопировать содержимое в файл boards.txt
 *** Путь к файлу C:\Users\[Имя пользователя]\Documents\Arduino\hardware\Arduino_STM32-master\STM32F1
 ** В меню "инструменты" выбрать USB Test (ST-Link)
 * 
 ** Связь со мной:
 ** YouTube https://www.youtube.com/channel/UCbkE52YKRphgkvQtdwzQbZQ
 ** Telegram https://www.t.me/slabyt
 ** Instagram https://www.instagram.com/romasklr
 ** VK https://vk.com/id395646965
 ** Facebook https://www.facebook.com/romasklyar94
 ** Twitter https://twitter.com/_SklyarRoman
 ** GitHub https://github.com/S-LABc
 * 
 ** COMPILED IN ARDUINO v1.8.13
 ** Copyright (C) 2021. v1.0 / Скляр Роман S-LAB
*/

#include <USBComposite.h>
#define ON  true
#define OFF false
/* Светодиод и вывод управленя USB */
#define LED_PIN      PC13
#define USB_DISC_PIN PB9
/* Задержка для миганий */
#define TIME_INIT_MS  500
#define TIME_START_MS 50
/* Создание HID и Keyboard на основе HID */
USBHID HID;
HIDKeyboard Keyboard(HID);

void setup() {
  enableDebugPorts();
  initLED();
  pinMode(USB_DISC_PIN, OUTPUT); // Вывод управления резистором
  conUSB(ON); // Подключить резистор
  HID.begin(HID_BOOT_KEYBOARD);
}

void loop() {  
  if (USBComposite) {
    blinkLED(TIME_START_MS);
  }
  else {
    blinkLED(TIME_INIT_MS);
  }
}

void conUSB(bool state) {
  if (state) {
    digitalWrite(USB_DISC_PIN, HIGH);
  }
  else {
    digitalWrite(USB_DISC_PIN, LOW);
  }
}

void initLED() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}
void blinkLED(uint32_t length) {
  delay(length);
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}
