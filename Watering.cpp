

#include "Watering.h"

Watering::Watering(
  byte moistureSensorPin, 
  byte moistureVCCOutputPin,
  byte hallMagneticSensorPin,
  byte waterPumpPin) {

  _moistureSensorPin = moistureSensorPin;
  _moistureVCCOutputPin = moistureVCCOutputPin;
  _hallMagneticSensorPin = hallMagneticSensorPin;
  _waterPumpPin = waterPumpPin;
  
}

void Watering::init() {

    pinMode(_moistureVCCOutputPin, OUTPUT);
    digitalWrite(_moistureVCCOutputPin, LOW);
    pinMode(_hallMagneticSensorPin, INPUT);
    pinMode(_waterPumpPin, OUTPUT);
    
    analogWrite(this->_waterPumpPin, 0);
  
}

void Watering::manageWatering() {

  int moistureSensorValue = 9000;

  // Watering plants until they have the right amount of water, or the tank is empty
  do {

    digitalWrite(_moistureVCCOutputPin, HIGH);
  
    delay(500);
  
    // Get the value of ground humidity
    moistureSensorValue = analogRead(_moistureSensorPin);
  
    Serial.print("Moisture sensor : ");
    Serial.println(moistureSensorValue);
  
    digitalWrite(_moistureVCCOutputPin, LOW);
  
    Serial.print("Hall magnetic sensor (is tank empty) : ");
    Serial.println(this->isTankEmpty());
  
    // If the tank is empty we can't send water to plants
    if(this->isTankEmpty() == false) {
      if(this->_lowThreshold > moistureSensorValue) {
         Serial.println("Ongoing watering");
         analogWrite(this->_waterPumpPin, 255);
         delay(1000);
      }
      
    }

  } while(this->_lowThreshold > moistureSensorValue && this->isTankEmpty() == false);

  analogWrite(this->_waterPumpPin, 0);
}

// The Hall magnetic sensor : http://www.banggood.com/5Pcs-DC-5V-KY-003-Hall-Magnetic-Sensor-Module-For-Arduino-p-954579.html
// When no magnet is near the sensor send 1
// When a magnet is near the sensor, he send 0
// So when 0 si send by the sensor, that mean that the trank is empty
bool Watering::isTankEmpty() {
  return digitalRead(_hallMagneticSensorPin) == 0;
}

