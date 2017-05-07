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

    String getTime();
    String getTime(DateTime now);

    /**
     * Return true if the hour is between the given boundary
     */
    boolean isHourBetweenBoundary(byte low, byte high);

    void updateForDST();

  private:
    RTC_DS1307 RTC;      // RTC Module Chip model on theTiny RTC i2C modul

    byte DST = 1; // Daylight Saving Time. If "1" it's summer time
    
    String leadingZeros(byte value);  
};

#endif
