/**
 * Manage the light
 */

#ifndef Lighting_h
#define Lighting_h

#include <Arduino.h>
#include "RealTimeClock.h"


class Lighting {

  public: 
    Lighting(byte lightSensorPin, byte lightOutputPin, RealTimeClock* rtc);
    void init();
    void manageLight();
    void enabledLight(bool isEnabled);
    int getAmbientLight();
    byte getAdditionnalLight();
    
  private:
    byte _lightSensorPin; // Arduino's analog pin link to the light resistor
    byte _lightOutputPin; // Arduino's PWM pin link to light
    RealTimeClock* _rtc;
    // We define the boundaries between which the light can be compensated
    byte _dayTimeStart = 7; // The day start à 7h
    byte _dayTimeEnd = 20; // The day end at 20h
    // Define if light is enabled
    bool _isEnabled = true;
    int _ambientLight;
    byte _additionnalLight;
};

#endif

