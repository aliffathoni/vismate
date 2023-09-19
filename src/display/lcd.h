#ifndef LCD_H_
#define LCD_H_

#include <Arduino.h>

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#include "../device_config.h"
#include "lcd_asset.h"

#define LCD_TAG "LCD"

typedef enum {
    // Main Menu
    HOME_SCREEN,
    NOTES,
    SPEAK,
    NAVIGATION,
    MAPS,
    SETTING,

    // Notes
    LISTENING,
    LOADING, // Extra
    SPEECH_TO_TEXT,
    LISTENING_RESULT,

    // Speak
    SPEAK_SAVED_PHRASE,
    SPEAK_GET_APP,
    SPEAK_PLAY_RESULT,

    // Navigation
    LOADING_OBJECT,
    OBJECT_DETECTION,

    // Maps
    HOME_MAPS,
    UNIV_MAPS,
    SHOW_MAPS,

    // Setting
    SET_VOLUME,
    SET_TIMEOUT,
    INFO_WIFI,
    SETTING_BACK,
    REBOOT
} Menu_screen_t;

#define small_font  4
#define big_font    6
#define number_font 7

class LCDClass {
    private:
        TFT_eSPI tft = TFT_eSPI();
        TFT_eSprite mainBg = TFT_eSprite(&tft);   //full
        TFT_eSprite bgSprite = TFT_eSprite(&tft);   //full
        TFT_eSprite iconSprite = TFT_eSprite(&tft); //tengah
        TFT_eSprite textSprite = TFT_eSprite(&tft); //boot & choose
        TFT_eSprite timeSprite = TFT_eSprite(&tft); //time & date

        uint16_t _rotate_angle = 0;
        String _string_buff;
    public:
        LCDClass(void);
        void init_tft(void);
        void menu(Menu_screen_t screen, int y_pos);
        void swipe(Menu_screen_t screen, int y_pos, uint16_t rotate_angle);
        void slide(Menu_screen_t screen, int x_pos, uint16_t rotate_angle);
        void show_logo();
        void show_device_logo();
        void update_time(String time, String date, int batt);
        void set_rotation(uint8_t rotation);
        void load(int progress, int rotate_angle);

        void moveTo(Menu_screen_t screen_name, int x_pos, int y_pos, uint16_t rotate_angle);
        void setBuff(String buff){
            _string_buff = buff;
        }
        uint8_t get_rotation();

        uint16_t get_angle(){
            return _rotate_angle;
        }
};

extern LCDClass lcd;

#endif // LCD_H_