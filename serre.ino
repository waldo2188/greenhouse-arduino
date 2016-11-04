/**
 * Greenhouse 
 * 
 * 
 */
 
#include <OneWire.h>            // OneWire
#include "RealTimeClock.h"
#include "Temperature.h"
#include "ManageTemperatureHumidity.h"
#include "Watering.h"
#include "Lighting.h"


#define OUTDSIDE_SENSOR_PIN 2   // Number of the temperature sensor's Pin connected to the Arduino
#define DHTPIN 4     // what pin we're connected to

#define FAN_PIN 3

#define MOISTURE_SENSOR_PIN A0 // This is an analog pin of Arduino for the moisture sensor
#define MOISTURE_VCC_OUTPUT_PIN 22 // This is useful to turn on or off the sensor and avoid rusting
#define HALL_MAGNETIC_SENSOR_PIN 26 // Pin for the Hall Magnetic sensor
#define WATER_PUMP_PIN 6 // This is the number of a PWM pin for turning on or off a water pump

#define LIGHT_SENSOR_PIN A1 // Arduino's analog input link to a light sensor
#define LIGHT_OUTPUT_PIN 5 // Arduino's PWM pin to manage light


OneWire oneWire(OUTDSIDE_SENSOR_PIN);          // OneWire, communication initialisation
 
RealTimeClock realTimeClock;
Temperature temperature(&oneWire, DHTPIN);
ManageTemperatureHumidity manageTemperatureHumidity(3);
Watering watering(MOISTURE_SENSOR_PIN, MOISTURE_VCC_OUTPUT_PIN, HALL_MAGNETIC_SENSOR_PIN, WATER_PUMP_PIN);
Lighting lighting(LIGHT_SENSOR_PIN, LIGHT_OUTPUT_PIN, &realTimeClock);

void setup() {
  Serial.begin(9600);

  // Initialise the Real Time Clock
  realTimeClock.init();

  // Initialise temperature sensors
  temperature.init();

  //manageTemperatureHumidity.init(fanPin);

  watering.init();

  lighting.init();
  
  Serial.println(realTimeClock.getLog("capteur", "INFO", "{temperature:10.87}", "Hey, jude"));

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

  lighting.manageLight();

  Serial.println("-------------------------------------------");
  Serial.println("");

  delay(5000);

}
