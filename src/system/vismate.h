#ifndef VISMATE_H_
#define VISMATE_H_

#include <Arduino.h>
#include "../device_config.h"
#include "../camera/object_detection.h"

class visMate {
    public :
        visMate();
        visMate(uint8_t pin);
        void init_camera();
        String get_object();
    private :
        int _pin = DEFAULT_EMG_PIN;
};

#endif // VISMATE_H_