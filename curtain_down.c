#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

void setup () {
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("Could not find DS3231");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC power lost, RTC module time is reset");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    Serial.println("Time is reset！");
  }
}

void loop () {
  DateTime now = rtc.now();

  if (now.dayOfTheWeek() >= 1 && now.dayOfTheWeek() <= 5 && now.hour() == 14 && now.minute() == 0 && now.second() == 0) {
    Serial.println("Time to coffee");
    alert_time(now);
    open_curtain();
  }
  
  delay(1000);
}

void open_curtain() {
  Serial.println("Open Curtain");
}

void alert_time(DateTime now) {
  String timeCommand = "Current Time is ";
  char buffer[20];
  sprintf(
    buffer, "%04d/%02d/%02d %02d:%02d:%02d", 
          now.year(), now.month(), now.day(), 
          now.hour(), now.minute(), now.second());
  Serial.print(timeCommand);
  Serial.println(buffer);
}
