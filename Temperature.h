/**
 * Temperature
 * 
 * Manage all temperature and humidity sensor
 */

 #include <Arduino.h>

class Temperature {

  public: 
    void init();
    float getInsideTemp();
    float getOutsideTemp();
    float getInsideHumidity();
};
 
