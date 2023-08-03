#ifndef VISMATE_H_
#define VISMATE_H_

#include <Arduino.h>
#include <Wire.h>
#include <string.h>
#include "../device_config.h"
#include "../network/network.h"
#include "../display/lcd.h"
#include "../speaker/voice.h"
#include "../sensor/range.h"

#define VIS_TAG "Vismate"

class VisMateClass {
    public :
        VisMateClass();
        void setup_control();
        void setup_control(uint8_t up_pin, uint8_t mid_pin, uint8_t down_pin);
        void init_connection();
        void init_i2c();
        void speaker_test();
        void lcd_test();
        void init_tof();
        void scan_i2c();
        void navigation_object();

        // Setting related function
        /*
         * @brief Change speaker volume, 0 to silent, 21 max
         *
         * @param volume Range volume point 0-21
         */
        void set_volume(uint8_t volume);
        uint8_t get_volume();
        void set_rotation(uint8_t rotation);
        uint8_t get_rotation();
        bool get_network_status();

        // Screen related function
        /*
         * @brief Set screen on menu
         * 
         * @param new_screen New screen destination
         */
        void screen(Menu_screen_t new_screen);

        /*
         * @brief Talkback new screen position
         *
         * @param new_screen New screen destination
         */
        void talk(Menu_screen_t new_screen);
        void openTo(Menu_screen_t app_screen);
        void backTo(Menu_screen_t last_screen);
        Menu_screen_t get_screen();
        Menu_screen_t get_last_screen();

    private :
        int _up_pin = DEFAULT_UP_PIN;
        int _mid_pin = DEFAULT_MID_PIN;
        int _down_pin = DEFAULT_DOWN_PIN;
        uint8_t _volume = 21;
        uint8_t _rotation;
        bool _network_status;

        Menu_screen_t _mode_screen;
        Menu_screen_t _screen_now;
        Menu_screen_t _last_screen;
};

extern VisMateClass vismate;

#endif // VISMATE_H_