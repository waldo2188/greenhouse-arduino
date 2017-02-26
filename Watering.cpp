
#include "Watering.h"

Watering::Watering(
  byte moistureSensorPin, 
  byte moistureVCCOutputPin,
  byte hallMagneticSensorPin,
  byte waterPumpPin,
  RealTimeClock* rtc) {

  _moistureSensorPin = moistureSensorPin;
  _moistureVCCOutputPin = moistureVCCOutputPin;
  _hallMagneticSensorPin = hallMagneticSensorPin;
  _waterPumpPin = waterPumpPin;
  _rtc = rtc;
  _moistureSensorSmoothedValue.init(10);
}

void Watering::init() {

    pinMode(_moistureVCCOutputPin, OUTPUT);
    digitalWrite(_moistureVCCOutputPin, LOW);
    pinMode(_hallMagneticSensorPin, INPUT);
    pinMode(_waterPumpPin, OUTPUT);
    
    analogWrite(this->_waterPumpPin, 0);
}

void Watering::manageWatering() {

  this->_hasBeenWatering = 0;

  // Turn on moisture sensor
  digitalWrite(_moistureVCCOutputPin, HIGH);
  // Allows the sensor to wake up
  delay(2000);

  // Get the value of ground humidity
  this->_moistureSensorValue = analogRead(_moistureSensorPin);
  _moistureSensorSmoothedValue.put(this->_moistureSensorValue);

  Serial.print("Moisture sensor : ");
  Serial.println(this->_moistureSensorValue);
  Serial.print("Smooth Moisture sensor : ");
  Serial.println(this->getSmoothMoisure());

  if(this->_rtc->isHourBetweenBoundary(_dayTimeStart, _dayTimeEnd) == false) {
    // Turn off moisture sensor
    digitalWrite(_moistureVCCOutputPin, LOW);
    return;
  }

  Serial.print("Hall magnetic sensor (is tank empty) : ");
  Serial.println(this->isTankEmpty());
  
  // Watering plants until they have the right amount of water, or the tank is empty
  do {
 
    // If the tank is empty we can't send water to plants
    if(this->isTankEmpty() == false) {
      if(this->_lowThreshold > this->getSmoothMoisure()) {
         Serial.println("Ongoing watering");
         analogWrite(this->_waterPumpPin, 255);
         delay(2000);
         this->_hasBeenWatering = this->_hasBeenWatering + 2;
      }
    }
    
    this->_moistureSensorValue = analogRead(_moistureSensorPin);
    _moistureSensorSmoothedValue.put(this->_moistureSensorValue);  
    
  } while(this->_lowThreshold > this->_moistureSensorValue && this->isTankEmpty() == false);

  analogWrite(this->_waterPumpPin, 0);
  // Turn off moisture sensor
  digitalWrite(_moistureVCCOutputPin, LOW);
}

// The Hall magnetic sensor : http://www.banggood.com/5Pcs-DC-5V-KY-003-Hall-Magnetic-Sensor-Module-For-Arduino-p-954579.html
// When no magnet is near the sensor send 1
// When a magnet is near the sensor, he send 0
// So when 0 si send by the sensor, that mean that the trank is empty
bool Watering::isTankEmpty() {
  return digitalRead(_hallMagneticSensorPin) == 0;
}

int Watering::hasBeenWatering() {
  return this->_hasBeenWatering;
}

int Watering::getMoisure() {
  return this->_moistureSensorValue;
}

int Watering::getSmoothMoisure() {
  return this->_moistureSensorSmoothedValue.read();
}
