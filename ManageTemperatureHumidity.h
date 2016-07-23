/**
 * Manage Temperature and Humidity in the Greenhouse
 * 
 * This class drive the fan for :
 *  - reduce humidity
 *  - reduce or increase temperature
 */

#include <Arduino.h>



class ManageTemperatureHumidity {

  public: 
    void init();
    void manageFan(float insideTemp, float outsideTemp, float insideHumidity);
    void setFanSpeed(byte fanSpeed);
};

