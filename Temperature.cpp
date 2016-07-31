
#include "Temperature.h"


// ------------------------------------------------------------------------------------------
// Init outside temperature sensor
#include <OneWire.h>            // OneWire
#include <DallasTemperature.h>  // DS18B20 For reading the temperature from the sensor

//#define OUTDSIDE_SENSOR_PIN 2   // Number of the temperature sensor's Pin connected to the Arduino
#define OUTDSIDE_SENSOR_RESOLUTION 12 // How many bits to use for temperature values: 9, 10, 11 or 12

//OneWire oneWire(OUTDSIDE_SENSOR_PIN);          // OneWire, communication initialisation
//DallasTemperature outsideSensors(&oneWire);   
//DallasTemperature _outsideSensors();

// End of init outside temperature sensor
// ------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------
// Init inside humidity and temperature sensor
#include <DHT.h>

#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT humidityTemperatureSensor(DHTPIN, DHTTYPE);
// End of inside humidity and temperature sensor
// ------------------------------------------------------------------------------------------

Temperature::Temperature(OneWire* wire) {
  this->_wire = wire;
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
  return humidityTemperatureSensor.readTemperature();
}

float Temperature::getInsideHumidity() {
  return humidityTemperatureSensor.readHumidity();
}

float Temperature::getOutsideTemp() {
  _outsideSensors.requestTemperatures();
  return _outsideSensors.getTempCByIndex(0);  
}

