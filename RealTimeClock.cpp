/**
   Talk with Tiny RTC(Real Time Clock) (DS1307)
*/

#include "RealTimeClock.h"

RealTimeClock::RealTimeClock() {}

void RealTimeClock::init() {
  // Initialisation of I2CrealTimeClock
  Wire.begin();

  // Initialisation of RTC
  RTC.begin();

  // Uncomment to update date and time
  // RTC.adjust(DateTime(__DATE__, __TIME__));

  // Check if RTC is up
  if (! RTC.isrunning()) {

    // Set the date and time if isn't defined
    RTC.adjust(DateTime(__DATE__, __TIME__));

    Serial.println("RTC is setup with system date and time");

  }  else {

    Serial.println("RTC is already up");

  }

  DateTime now = RTC.now(); // Get RTC date time

  // Last sunday of March
  DateTime startSum = DateTime(now.year(), 3, 25, 3, 0, 0);

  while (startSum.dayOfTheWeek() != 0) {
    startSum = DateTime(startSum.unixtime() + 86400);
  }

  // Last sunday of October
  DateTime endSum = DateTime(now.year(), 10, 25, 2, 0, 0);

  while (endSum.dayOfTheWeek() != 0) {
    endSum = DateTime(endSum.unixtime() + 86400);
  }

  DST = 0;
  if (now.unixtime() >= startSum.unixtime() && now.unixtime() <= endSum.unixtime()) {
    DST = 1;
  }

  RTC.writenvram(0, DST);
}

RTC_DS1307 RealTimeClock::getRTC() {
  return RTC;
}

boolean RealTimeClock::isHourBetweenBoundary(byte low, byte high) {
  byte currentHour = RTC.now().hour();

  if (low <= currentHour && currentHour <= high) {
    return true;
  }

  return false;
}

String RealTimeClock::getTime() {

   return this->getTime(RTC.now());
   
}

String RealTimeClock::getTime(DateTime now) {

  String logString = "";
  
  // Format Date time
  logString = String(now.year(), DEC) + "-" + RealTimeClock::leadingZeros(now.month()) + "-" + RealTimeClock::leadingZeros(now.day()) + " ";
  logString = logString + RealTimeClock::leadingZeros(now.hour()) + ":" + RealTimeClock::leadingZeros(now.minute()) + ":" + RealTimeClock::leadingZeros(now.second());

  return logString;
}

/**
   Update the RTC for matching the Daylight Saving Time
   http://www.instructables.com/id/The-Arduino-and-Daylight-Saving-Time-Europe/
*/
void RealTimeClock::updateForDST() {

  DST = RTC.readnvram(0);

  DateTime now = RTC.now(); // Get RTC date time

  byte dow = now.dayOfTheWeek(); // day of week (as in 1-7)
  byte mo = now.month(); // Month
  byte d = now.day(); // Day
  byte h = now.hour(); // Hour

  if (dow == 7 && mo == 10 && d >= 25 && h == 3 && DST == 1)
  {
    RTC.adjust(DateTime(now.unixtime() - 3600));
    DST = 0;
  }

  if (dow == 7 && mo == 3 && d >= 25 && h == 2 && DST == 0)
  {
    RTC.adjust(DateTime(now.unixtime() + 3600));
    DST = 1;
  }

  RTC.writenvram(0, DST);
}

/**
   Add leading zero to have a two-digit number

   @param int value
   @return String
*/
String RealTimeClock::leadingZeros(byte value) {
  if (value < 10) {
    return "0" + String(value, DEC);
  }

  return String(value, DEC);
}
