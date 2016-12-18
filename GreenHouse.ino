/**
 * Greenhouse 
 * 
 * 
 */
#include "Config.h" 
#include <OneWire.h>            // OneWire
#include "RealTimeClock.h"
#include "Temperature.h"
#include "ManageTemperatureHumidity.h"
#include "Watering.h"
#include "Lighting.h"
#include "GreenWifi.h"



#define OUTDSIDE_SENSOR_PIN 22   // Number of the temperature sensor's Pin connected to the Arduino
#define DHTPIN 26     // what pin we're connected to

#define FAN_PIN 3

#define MOISTURE_SENSOR_PIN A1 // This is an analog pin of Arduino for the moisture sensor
#define MOISTURE_VCC_OUTPUT_PIN A2 // This is useful to turn on or off the sensor and avoid rusting
#define HALL_MAGNETIC_SENSOR_PIN 24 // Pin for the Hall Magnetic sensor
#define WATER_PUMP_PIN 6 // This is the number of a PWM pin for turning on or off a water pump

#define LIGHT_SENSOR_PIN A0 // Arduino's analog input link to a light sensor
#define LIGHT_OUTPUT_PIN 5 // Arduino's PWM pin to manage light


OneWire oneWire(OUTDSIDE_SENSOR_PIN);          // OneWire, communication initialisation
 
RealTimeClock realTimeClock;
Temperature temperature(&oneWire, DHTPIN);
// 
ManageTemperatureHumidity manageTemperatureHumidity(FAN_PIN);
Watering watering(MOISTURE_SENSOR_PIN, MOISTURE_VCC_OUTPUT_PIN, HALL_MAGNETIC_SENSOR_PIN, WATER_PUMP_PIN);
Lighting lighting(LIGHT_SENSOR_PIN, LIGHT_OUTPUT_PIN, &realTimeClock);
GreenWifi gWifi;


void setup() {
  Serial.begin(9600);
  // initialize serial for ESP WiFi module
  Serial1.begin(115200);

  static HttpServerHandler myServerHandlers[] = {
    { "GET /light", switchLight }
  };

  gWifi.init(&Serial1, WIFI_SSID, WIFI_PASSWORD, myServerHandlers, API_THINGSPEAK_KEY);

  // Initialise the Real Time Clock
  realTimeClock.init();

  // Initialise temperature sensors
  temperature.init();


  watering.init();

  lighting.init();

  // TODO remove when Wifi server will work
  //switchLight("on");
}

void loop() { 

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

  gWifi.logData(
    temperature.getOutsideTemp(),
    temperature.getInsideTemp(),
    temperature.getInsideHumidity(),
    manageTemperatureHumidity.getFanSpeed(),
    lighting.getAmbientLight(),
    lighting.getAdditionnalLight()
    );

  // 5minutes
  delay(300000);

  // TODO Don't work for now
  /*long startMillis = millis();
  do {
    gWifi.handleRequest();
    delay(1000);
  } while (millis() - startMillis < 10000);*/
 
}

void switchLight(String query) {
  query.toLowerCase();
  lighting.enabledLight(query == "on");
}
