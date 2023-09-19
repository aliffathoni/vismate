#ifndef Battery_h_
#define Battery_h_

#include <Arduino.h>

class BatteryClass {
  private:
    uint8_t _pin = 4;
  public:
    BatteryClass();
    void begin();
    uint8_t get_percentage();
    float get_voltage();
};

extern BatteryClass battery;

#endif // Battery_h_