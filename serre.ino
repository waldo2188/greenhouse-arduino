/**
 * Greenhouse 
 * 
 * 
 */

#include "RealTimeClock.h"
#include "Temperature.h"
#include "ManageTemperatureHumidity.h"
#include "Watering.h";
 
RealTimeClock realTimeClock;
Temperature temperature;
ManageTemperatureHumidity manageTemperatureHumidity(3);
Watering watering(A0, 8);


void setup() {
  Serial.begin(9600);

  // Initialise the Real Time Clock
  realTimeClock.init();

  // Initialise temperature sensors
  temperature.init();

  //manageTemperatureHumidity.init(fanPin);

  watering.init();
  
  Serial.println(realTimeClock.getLog("capteur", "INFO", "{temperature:10.87}", "Hey, jude, ma cocote"));

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print("Outside temperature ");
  Serial.print(temperature.getOutsideTemp());
  Serial.println("°C");

  Serial.print("Inside temperature ");
  Serial.print(temperature.getInsideTemp());
  Serial.println("°C");

  Serial.print("Inside humidity ");
  Serial.print(temperature.getInsideHumidity());
  Serial.println("%");  

  Serial.println("-------------------------------------------");

  manageTemperatureHumidity.manageFan(
    temperature.getInsideTemp(),
    temperature.getOutsideTemp(),
    temperature.getInsideHumidity()
    );

  watering.manageWatering();

  delay(5000);

}
