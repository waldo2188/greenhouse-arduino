
#include <Arduino.h>
#include "ManageTemperatureHumidity.h"

ManageTemperatureHumidity::ManageTemperatureHumidity(byte fanPin) {

  this->_fanPin = fanPin;
  // Init pin
  pinMode(_fanPin, OUTPUT);
}

void ManageTemperatureHumidity::manageFan(float insideTemp, float outsideTemp, float insideHumidity) {
  _fanSpeed = 0;

  // Check if it's to cold inside the greenhouse
  if (insideTemp <= (this->_idealLowtemperature) && outsideTemp > insideTemp) {
    //TODO refine the bounds
    _fanSpeed = map((this->_idealLowtemperature - insideTemp), 0, 20, 100, 255);
  }

  // Check if it's to hot inside the greenhouse
  if (insideTemp >= _idealHightemperature && outsideTemp <= insideTemp) {
    //TODO refine the bounds
    _fanSpeed = map((insideTemp - this->_idealHightemperature), 0, 20, 100, 255);
  }

  if (insideHumidity > this->_idealHighHumidity) {
    //TODO refine the bounds
    _fanSpeed = map((insideHumidity - this->_idealHighHumidity), 0, 20, 100, 255);
  }
  
  Serial.print("Fan speed : ");
  Serial.println(_fanSpeed);

  if (_fanSpeed > 0) {
    this->setFanSpeed(_fanSpeed);
  } else {
    this->setFanSpeed(0);
  }
}

/**
   fanSpeed must be between 60 and 255
*/
void ManageTemperatureHumidity::setFanSpeed(byte fanSpeed) {
  analogWrite(this->_fanPin, fanSpeed);
}

byte ManageTemperatureHumidity::getFanSpeed() {
  return _fanSpeed;
}

