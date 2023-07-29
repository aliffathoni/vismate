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
        void setup_control();
        void setup_control(uint8_t up_pin, uint8_t mid_pin, uint8_t down_pin);
        void init_i2c();
        void speaker_test();
        void lcd_test();
        void scan_i2c();
        void screen(Menu_screen_t new_screen);
        Menu_screen_t get_screen();

    private :
        int _up_pin = DEFAULT_UP_PIN;
        int _mid_pin = DEFAULT_MID_PIN;
        int _down_pin = DEFAULT_DOWN_PIN;

        Menu_screen_t _screen_now;
        Menu_screen_t _last_screen;
};

extern VisMateClass vismate;

#endif // VISMATE_H_