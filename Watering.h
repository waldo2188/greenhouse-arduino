/**
   Watering

   Manage watering plants
*/

#include <Arduino.h>

class Watering {

  public:
    Watering(byte moistureSensorPin, byte moistureVCCOutputPin, byte hallMagneticSensorPin, byte waterPumpPin);
    void init();
    void manageWatering();

  private:
    byte _moistureSensorPin; // This is an analog pin of Arduino
    byte _moistureVCCOutputPin; // VCC pin for turn on the sensor
    byte _hallMagneticSensorPin; // This is a numeric pin for the Hall Magnetic sensor
    byte _waterPumpPin; // This is a numeric PWM pin for the water pump
    bool isTankEmpty(); // return TRUE is the tank is empty
    int _lowThreshold = 500;
};

