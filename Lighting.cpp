
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

  // 1023 mean no light at all
  // 0 mean a lot of light
  // So with map we inverse the value and at the end  
  // 0 mean no light at all
  // 1023 mean a lot of light
  _ambientLight = map(analogRead(_lightSensorPin), 0, 1023, 1023, 0);

  Serial.print("Amount of light : ");
  Serial.println(_ambientLight);

  byte actualHour = this->_rtc->getRTC().now().hour();

  // Light On !
  if (_isEnabled && _dayTimeStart <= actualHour && actualHour <= _dayTimeEnd) {

    //_additionnalLight = map(_ambientLight, 0, 1023, 255, 0); 
    //Serial.print("Compensating lighting : ");
    //Serial.println(_additionnalLight);

    // Allways the max amount of light
    analogWrite(_lightOutputPin, 255);
    
  } else {
    // Light Off !
    analogWrite(_lightOutputPin, 0);
  }
}

void Lighting::enabledLight(bool isEnabled) {
  _isEnabled = isEnabled;
}

int Lighting::getAmbientLight() {
  return _ambientLight;
}

byte Lighting::getAdditionnalLight() {
  return _additionnalLight;
}


