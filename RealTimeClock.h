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

    RTC_DS1307 getRTC();

  private:
    RTC_DS1307 RTC;      // RTC Module Chip model on theTiny RTC i2C modul
};

#endif
