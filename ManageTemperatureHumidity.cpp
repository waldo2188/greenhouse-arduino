
#include "ManageTemperatureHumidity.h"


byte idealLowtemperature = 18; // unit is °C
byte idealHightemperature = 30; // unit is °C
byte idealHighHumidity = 80; // unit is %

/**
 * The Fan is plug on a PWN output and use a mosfet.
 * 
 * The minimus output for analoWrite funcion is 60.
 * Under 60 the Fan won't start and make strange noise... (Maybe my fan is a little bit shitty)
 */
byte fanPin = 3; // Fan on a PWN pin

void ManageTemperatureHumidity::ManageTemperatureHumidity::init() {

  // Init pin
  pinMode(fanPin, OUTPUT);
}

void ManageTemperatureHumidity::manageFan(float insideTemp, float outsideTemp, float insideHumidity) {
  bool turnOnFan = false;
  byte fanSpeed = 0;

  // Check if it's to cold inside the greenhouse
  if(insideTemp <= (idealLowtemperature) && outsideTemp > insideTemp) {
    turnOnFan = true;
    fanSpeed = map((idealLowtemperature - insideTemp), 0, 20, 60, 255);
  }

  // Check if it's to hot inside the greenhouse
  if(insideTemp >= idealHightemperature && outsideTemp <= insideTemp) {
    turnOnFan = true;
    fanSpeed = map((insideTemp - idealHightemperature), 0, 20, 60, 255);
  }

  if(insideHumidity > idealHighHumidity) {
    fanSpeed = map((insideHumidity - idealHighHumidity), 0, 20, 60, 255);
    turnOnFan = true;
  }

  Serial.print("Speed fan");
  Serial.println(fanSpeed);

  if (turnOnFan == true) {
    this->setFanSpeed(fanSpeed);
  } else {
    this->setFanSpeed(0);
  }
}

/**
 * fanSpeed must be between 60 and 255
 */
void ManageTemperatureHumidity::setFanSpeed(byte fanSpeed) {
  analogWrite(fanPin, fanSpeed);
}

