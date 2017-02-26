#include "SmoothingValue.h"

SmoothingValue::SmoothingValue() {}

SmoothingValue::init(byte size) {
  _size = size;
  _next = 0;

  if (_values != 0) {
    _values = (int*) realloc(_values, _size * sizeof(int));
  } else {
    _values = (int*) malloc(_size * sizeof(int));
  }

  _isInit = false;
}

void SmoothingValue::put(int value) {
  _values[_next] = value;

  if (_isInit == false) {
    for (byte i = 0; i < _size; i++) {
      _values[i] = value;
    }
    _isInit = true;
  }

  _next++;

  if (_next >= _size ) {
    _next = 0;
  }
}

float SmoothingValue::read() {
  float sum = 0;
  for (byte i = 0; i < _size; i++) {
    sum = sum + _values[i];
  }
  return sum / _size;
}

