/**
 * Manage Temperature and Humidity in the Greenhouse
 * 
 * This class drive the fan for :
 *  - reduce humidity
 *  - reduce or increase temManageTemperatureHumidity(byte fanPin)perature
 */
 
#ifndef ManageTemperatureHumidity_h
#define ManageTemperatureHumidity_h

#include <Arduino.h>



class ManageTemperatureHumidity {

  public: 
    ManageTemperatureHumidity(byte fanPin);
    void manageFan(float insideTemp, float outsideTemp, float insideHumidity);
    void setFanSpeed(byte fanSpeed);

  private:
  /**
   * The Fan is plug on a PWN output and use a mosfet.
   * 
   * The minimus output for analoWrite funcion is 60.
   * Under 60 the Fan won't start and make strange noise... (Maybe my fan is a little bit shitty)
   */
    byte _fanPin;
    byte _idealLowtemperature = 18; // unit is °C
    byte _idealHightemperature = 30; // unit is °C
    byte _idealHighHumidity = 80; // unit is %

};

#endif

