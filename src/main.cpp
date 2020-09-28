// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTClib.h"

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

class Relay{
  int relayPin;
  int relayState;

  public:
  Relay(int pin){
    relayPin = pin;
    pinMode(relayPin, OUTPUT);

    relayState = HIGH;

  }

  void On(){
    relayState = LOW;
    digitalWrite(relayPin, relayState);
  }


  void Off(){
    relayState = HIGH;
    digitalWrite(relayPin, relayState);
  }
};

Relay relay1(D3);

void setup () {

  if (! rtc.begin()) {
    abort();
  }

  if (! rtc.isrunning()) {  
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop () {
    DateTime now = rtc.now();
    int current_hour = now.hour();
    
    if(current_hour >= 5 && current_hour <= 18){
      relay1.On();
    } else {
      relay1.Off();
    }
}