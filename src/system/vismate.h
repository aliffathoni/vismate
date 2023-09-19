#ifndef VISMATE_H_
#define VISMATE_H_

#include <Arduino.h>
#include <Wire.h>
#include <string.h>
#include "../device_config.h"
#include "../network/network.h"
#include "network/firebase.h"
#include "../display/lcd.h"
#include "../speaker/voice.h"
#include "../sensor/range.h"
#include "../control/rotary.h"
#include "../sensor/battery.h"
#include "driver/rtc_io.h"
#include "soc/soc_caps.h"
#include <HardwareSerial.h>
#include "ArduinoJson.h"

#define VIS_TAG "Vismate"

class VisMateClass {
    public :
        VisMateClass();
        void setup_control();
        void init_connection();
        void init_i2c();
        void speaker_test();
        void init_lcd();
        void init_tof();
        void scan_i2c();
        void navigation_object();
        void set_volume(uint8_t volume);
        uint8_t get_volume();
        void set_rotation(uint8_t rotation);
        uint8_t get_rotation();
        bool get_network_status();

        float get_angle();

        // screen related
        void screen(Menu_screen_t new_screen);
        void talk(Menu_screen_t screen_name);
        Menu_screen_t get_screen();
        Menu_screen_t get_last_screen();
        void setScreen(Menu_screen_t screen_name);
    private :
        int _button_pin = DEFAULT_BUTTON_PIN;

        uint8_t _volume = 21;
        uint8_t _rotation;
        bool _network_status;
        bool _sleep = false;

        Menu_screen_t _mode;
        Menu_screen_t _screen_now;
        Menu_screen_t _last_screen;

        void IRAM_ATTR rotary_ISR();
        void IRAM_ATTR sleep_ISR();
};

extern VisMateClass vismate;

#endif // VISMATE_H_