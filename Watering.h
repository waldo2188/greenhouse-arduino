/**
   Watering

   Manage watering plants
*/

#include <Arduino.h>
#include "RealTimeClock.h"
#include "SmoothingValue.h"

class Watering {

  public:
    Watering(byte moistureSensorPin, byte moistureVCCOutputPin, byte hallMagneticSensorPin, byte waterPumpPin, RealTimeClock* rtc);
    void init();
    void manageWatering();
    int getMoisure();
    int getSmoothMoisure();
    int hasBeenWatering();

  private:
    // We define the boundaries between which the water pump can be used
    byte _dayTimeStart = 9; // The day start à 8h, cause my little girl need to sleep ;)
    byte _dayTimeEnd = 19; // The day end at 20h
    byte _moistureSensorPin; // This is an analog pin of Arduino
    byte _moistureVCCOutputPin; // VCC pin for turn on the sensor
    byte _hallMagneticSensorPin; // This is a numeric pin for the Hall Magnetic sensor
    byte _waterPumpPin; // This is a numeric PWM pin for the water pump
    bool isTankEmpty(); // return TRUE is the tank is empty
    int _lowThreshold = 380;
    int _moistureSensorValue = 800;
    SmoothingValue _moistureSensorSmoothedValue;
    int _hasBeenWatering = 0;
    RealTimeClock* _rtc;
};
