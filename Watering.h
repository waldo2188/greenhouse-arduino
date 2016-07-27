/**
   Watering

   Manage watering plants
*/

#include <Arduino.h>

class Watering {

  public:
    Watering(byte moistureSensorPin, byte moistureVCCOutputPin);
    void init();
    void manageWatering();

  private:
    byte _moistureSensorPin; // This is an analog pin of Arduino
    byte _moistureVCCOutputPin; // VCC pin for turn on the sensor
};

