/**
   Temperature

   Manage all temperature and humidity sensor
*/


#ifndef Temperature_h
#define Temperature_h

#include <Arduino.h>
#include <OneWire.h>            // OneWire
#include <DallasTemperature.h>  // DS18B20 For reading the temperature from the sensor
#include "dht.h"

class Temperature {

  public:
    Temperature(OneWire* wire, byte dhtPin);
    void init();
    float getInsideTemp();
    float getOutsideTemp();
    float getInsideHumidity();

  private:
    // Init outside temperature sensor
    OneWire* _wire; // OneWire, communication initialisation
    byte _dhtPin; // The number of the pin where the DHT sensor is connected
    DallasTemperature _outsideSensors; // DS18B20, temperature sensor initialisation
    DeviceAddress _outsideSensorsDeviceAddress;
    dht DHT;
    double _temperature;
    double _humidity;
};

#endif

