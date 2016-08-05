/**
 * Talk with Tiny RTC(Real Time Clock) (DS1307)
 */

#include "RealTimeClock.h"

RealTimeClock::RealTimeClock() {}

void RealTimeClock::init() {
  // Initialisation of I2C
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

/**
 * RealTimeClock::getLog
 * @exemple [2016-03-07 08:43:22] capteur.INFO: {“temperature_int”: 20} [“capteur”]
 * 
 * @param String channel
 * @param String levelName [DEBUG|INFO|WARNING|EMERGENCY]
 * @param String Message
 * @param String Context
 * @return String
 */
String RealTimeClock::getLog(String channel, String levelName, String Message, String Context) {

  String logString = "";

  DateTime now = RTC.now(); // Get RTC date time

  // Format Date time
  logString = "[" + String(now.year(), DEC) + "-" + RealTimeClock::leadingZeros(now.month()) + "-" + RealTimeClock::leadingZeros(now.day()) + " ";
  logString = logString + RealTimeClock::leadingZeros(now.hour()) + ":" + RealTimeClock::leadingZeros(now.minute()) + ":" + RealTimeClock::leadingZeros(now.second()) + "] ";

  // Format channel and log level name
  logString = logString + channel + "." + levelName + ": ";

  // Add the message
  logString = logString + Message + " ";
  
  // Add the contexte
  logString = logString + "[" + Context + "]";
  
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

