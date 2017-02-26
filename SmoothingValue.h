/**
   Smooth
*/

#ifndef SmoothingValue_h
#define SmoothingValue_h

#include <Arduino.h>

class SmoothingValue {

  public:
    SmoothingValue();
    init(byte size);
    void put(int value);
    float read();

  private:
    byte _size; // The number of values we have to store
    int* _values = 0;
    byte _next; // Store the next index where we have toi save the value
    bool _isInit = false;
};

#endif
