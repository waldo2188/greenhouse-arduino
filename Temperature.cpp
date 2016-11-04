
#include "Temperature.h"


// ------------------------------------------------------------------------------------------
// Special configuration for outside temperature sensor
#define OUTDSIDE_SENSOR_RESOLUTION 12 // How many bits to use for temperature values: 9, 10, 11 or 12

// ------------------------------------------------------------------------------------------
// Special configuration for inside humidity and temperature sensor
#define DHTTYPE DHT22   // DHT 22 (AM2302), type of the sensor


Temperature::Temperature(OneWire* wire, byte dhtPin) {
  this->_wire = wire;
  this->_dhtPin = dhtPin;
}

void Temperature::init() {
  
  this->_outsideSensors = DallasTemperature(this->_wire);
  
  DeviceAddress _outsideSensorsDeviceAddress;
 
  _outsideSensors.begin();  // DS18B20 initialise bus
  _outsideSensors.getAddress(_outsideSensorsDeviceAddress, 0);
  // Set the accuracy of the temperature measurement
  _outsideSensors.setResolution(_outsideSensorsDeviceAddress, OUTDSIDE_SENSOR_RESOLUTION);
}

float Temperature::getInsideTemp() {

  int chk = DHT.read22(this->_dhtPin);

  if (chk == DHTLIB_OK) {
    _temperature = DHT.temperature;
    _humidity = DHT.humidity;
    return _temperature;
  } 

  return _temperature;
}

float Temperature::getInsideHumidity() {
  int chk = DHT.read22(this->_dhtPin);

  if (chk == DHTLIB_OK) {
    _temperature = DHT.temperature;
    _humidity = DHT.humidity;
  }

  return _humidity;
}

     

float Temperature::getOutsideTemp() {
  _outsideSensors.requestTemperatures();
  return _outsideSensors.getTempCByIndex(0);  
}

