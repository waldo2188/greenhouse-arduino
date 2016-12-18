
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
  _ambientLight = analogRead(_lightSensorPin);

  Serial.print("Amount of light : ");
  Serial.println(_ambientLight);

  byte actualHour = this->_rtc->getRTC().now().hour();

  // Light On !
  if (_isEnabled && _ambientLight < 800 && _dayTimeStart <= actualHour && actualHour <= _dayTimeEnd) {

    _additionnalLight = map(_ambientLight, 0, 1023, 255, 0);
     
    Serial.print("Compensating lighting : ");
    Serial.println(_additionnalLight);

    analogWrite(_lightOutputPin, _additionnalLight);
    
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


