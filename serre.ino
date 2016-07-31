/**
 * Greenhouse 
 * 
 * 
 */
 
#include <OneWire.h>            // OneWire
#include "RealTimeClock.h"
#include "Temperature.h"
#include "ManageTemperatureHumidity.h"
#include "Watering.h";

#define OUTDSIDE_SENSOR_PIN 2   // Number of the temperature sensor's Pin connected to the Arduino
#define DHTPIN 4     // what pin we're connected to

OneWire oneWire(OUTDSIDE_SENSOR_PIN);          // OneWire, communication initialisation
 
RealTimeClock realTimeClock;
Temperature temperature(&oneWire, DHTPIN);
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

  manageTemperatureHumidity.manageFan(
    temperature.getInsideTemp(),
    temperature.getOutsideTemp(),
    temperature.getInsideHumidity()
    );

  watering.manageWatering();

  Serial.println("-------------------------------------------");
  Serial.println("");

  delay(5000);

}
