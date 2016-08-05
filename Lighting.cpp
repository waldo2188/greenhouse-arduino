
#include "Lighting.h";


Lighting::Lighting(byte lightSensorPin, byte lightOutputPin, RealTimeClock* rtc) {
  _lightSensorPin = lightSensorPin;
  _lightOutputPin = lightOutputPin;
  _rtc = rtc;
}

void Lighting::init() {
  pinMode(_lightSensorPin, INPUT);
  pinMode(_lightOutputPin, OUTPUT);

  analogWrite(_lightOutputPin, 0);
}


void Lighting::manageLight() {

  // O mean no light at all
  // 1023 mean a lot of light
  int amontOfLight = analogRead(_lightSensorPin);

  Serial.print("Amount of light : ");
  Serial.println(amontOfLight);

  byte actualHour = this->_rtc->getRTC().now().hour();
  

  // Light On !
  if (amontOfLight < 800 && _dayTimeStart <= actualHour && actualHour <= _dayTimeEnd) {

    byte lightNeed = map(amontOfLight, 0, 1023, 255, 0);
     
    Serial.print("Compensating lighting : ");
    Serial.println(lightNeed);

    analogWrite(_lightOutputPin, lightNeed);
    
  } else {
    // Light Off !
    analogWrite(_lightOutputPin, 0);
  }
  
}

