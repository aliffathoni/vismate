#ifndef VISMATE_H_
#define VISMATE_H_

#include <Arduino.h>
#include <Wire.h>
#include "../device_config.h"
#include "../network/network.h"
#include "../display/lcd.h"
#include "../speaker/voice.h"

class VisMateClass {
    public :
        VisMateClass();
        void init_i2c();
        void speaker_test();
        void lcd_test();
        void scan_i2c();
        
    private :
        int _pin;
};

extern VisMateClass vismate;

#endif // VISMATE_H_