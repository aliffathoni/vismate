#ifndef RANGE_H_
#define RANGE_H_

#include <Arduino.h>


class ToFClass {
    private:
        const int _sda = 8;
        const int _scl = 9;

    public:
        ToFClass(void);
        void begin(void);
        int get_meter();
        int get_centi();
        int get_mili();
};

extern ToFClass tof;

#endif // RANGE_H_
