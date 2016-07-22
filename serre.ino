/**
 * Greenhouse 
 * 
 * 
 */

 #include "RealTimeClock.h"
 #include "Temperature.h"

RealTimeClock realTimeClock;
Temperature temperature;

void setup() {
  Serial.begin(9600);

  // Initialise the Real Time Clock
  realTimeClock.init();

  // Initialise temperature sensors
  temperature.init();

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


  delay(20000);

}
