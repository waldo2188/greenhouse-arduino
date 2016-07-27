

#include "Watering.h"

Watering::Watering(byte moistureSensorPin, byte moistureVCCOutputPin) {

  _moistureSensorPin = moistureSensorPin;
  _moistureVCCOutputPin = moistureVCCOutputPin;
  
}

void Watering::init() {

    pinMode(_moistureVCCOutputPin, OUTPUT);
    digitalWrite(_moistureVCCOutputPin, LOW);
  
}

void Watering::manageWatering() {

  digitalWrite(_moistureVCCOutputPin, HIGH);

  delay(500);

  int moistureSensorValue = analogRead(_moistureSensorPin);

  Serial.print("Moisture sensor : ");
  Serial.println(moistureSensorValue);

  digitalWrite(_moistureVCCOutputPin, LOW);  
}

