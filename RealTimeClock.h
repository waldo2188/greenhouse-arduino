/**
 * Talk with Tiny RTC(Real Time Clock) (DS1307)
 * 
 * Usefull for generating log
 */

#ifndef RealTimeClock_h
#define RealTimeClock_h

#include <Arduino.h>

// Tiny RTC(Real Time Clock) (DS1307)
// @see http://blog.simtronyx.de/en/tiny-rtc-ds1307-real-time-clock-with-an-additional-temperature-sensor-ds18b20/
#include <Wire.h>    // I2C-library
#include "RTClib.h"  // RTC-library

class RealTimeClock {

  public:
    RealTimeClock();

    /**
       Initialise communication with RTC module
    */
    void init();

    /**
       Return Log

       exemple : [2016-07-13 15:16:57] capteur.INFO: {temperature:10.87} [capteur, inside]
    */
    String getLog(String channel, String levelName, String Message, String Context);

    /**
       Add leading zero to have a two-digit number

       @param int value
       @return String
    */
    static String leadingZeros(byte value);

    RTC_DS1307 getRTC();

  private:
    RTC_DS1307 RTC;      // RTC Module Chip model on theTiny RTC i2C modul
};

#endif
