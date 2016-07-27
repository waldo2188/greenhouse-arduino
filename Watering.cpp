
#include "Watering.h"

byte moistureSensorPin = A0; // This is an analog pin of Arduino
byte moistureVCCOutputPin = 8; // VCC pin for turn on the sensor


void Watering::init() {

    pinMode(moistureVCCOutputPin, OUTPUT);
    digitalWrite(moistureVCCOutputPin, LOW);
  
}

void Watering::manageWatering() {

  digitalWrite(moistureVCCOutputPin, HIGH);

  delay(500);

  int moistureSensorValue = analogRead(moistureSensorPin);

  Serial.print("Moisture sensor : ");
  Serial.println(moistureSensorValue);

  digitalWrite(moistureVCCOutputPin, LOW);  
}

