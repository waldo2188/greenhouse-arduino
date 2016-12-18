/**
 * Talk with Tiny RTC(Real Time Clock) (DS1307)
 */

#include "RealTimeClock.h"

RealTimeClock::RealTimeClock() {}

void RealTimeClock::init() {
  // Initialisation of I2CrealTimeClock
  Wire.begin();

  // Initialisation of RTC
  RTC.begin();

  // Check if RTC is up
  if (! RTC.isrunning()) {

    // Set the date and time if isn't defined
    RTC.adjust(DateTime(__DATE__, __TIME__));

    Serial.println("RTC is setup with system date and time");
    
  }  else {
    
    Serial.println("RTC is already up");
    
  }
 
}

RTC_DS1307 RealTimeClock::getRTC() {
  return RTC;
}

