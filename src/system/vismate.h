#ifndef VISMATE_H_
#define VISMATE_H_

#include <Arduino.h>

class visMate {
    public :
        visMate();
        visMate(uint8_t pin);
        void init_camera();
        String get_object();
    private :
        int _pin;
};

#endif // VISMATE_H_