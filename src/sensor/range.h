#ifndef RANGE_H_
#define RANGE_H_

#include <Arduino.h>
#include "Adafruit_VL53L0X.h"

class ToFClass {
    private:
        Adafruit_VL53L0X lox = Adafruit_VL53L0X();
        
    public:
        ToFClass(void);
        void begin(void);
        String get_range();
        int get_meter();
        int get_centi();
        int get_mili();
};

extern ToFClass tof;

#endif // RANGE_H_
