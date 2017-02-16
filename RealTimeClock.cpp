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

boolean RealTimeClock::isHourBetweenBoundary(byte low, byte high) {
  byte currentHour = RTC.now().hour();

  if(low <= currentHour && currentHour <= high) {
    return true;
  }

  return false;
}

String RealTimeClock::getTime() {
  
  String logString = "";

  DateTime now = RTC.now(); // Get RTC date time

  // Format Date time
  logString = String(now.year(), DEC) + "-" + RealTimeClock::leadingZeros(now.month()) + "-" + RealTimeClock::leadingZeros(now.day()) + " ";
  logString = logString + RealTimeClock::leadingZeros(now.hour()) + ":" + RealTimeClock::leadingZeros(now.minute()) + ":" + RealTimeClock::leadingZeros(now.second());
  
  return logString;
}

/**
 * Add leading zero to have a two-digit number
 * 
 * @param int value
 * @return String
 */
String RealTimeClock::leadingZeros(byte value) {
  if(value < 10) {
    return "0" + String(value, DEC);
  }
  
  return String(value, DEC);
}
