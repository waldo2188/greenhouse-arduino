/**
   Temperature

   Manage all temperature and humidity sensor
*/


#ifndef Temperature_h
#define Temperature_h

#include <Arduino.h>

class Temperature {

  public:
    void init();
    float getInsideTemp();
    float getOutsideTemp();
    float getInsideHumidity();
};

#endif

