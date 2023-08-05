#ifndef LCD_H_
#define LCD_H_

#include <Arduino.h>

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#include "../device_config.h"
#include "lcd_asset.h"

// #define LCD_DEBUG
#define LCD_TAG "LCD"

#define small_font  4
#define big_font    6
#define number_font 7

class LCDClass {
    private:
        TFT_eSPI tft = TFT_eSPI();
        TFT_eSprite bgSprite = TFT_eSprite(&tft);   //full
        TFT_eSprite iconSprite = TFT_eSprite(&tft); //tengah
        TFT_eSprite textSprite = TFT_eSprite(&tft); //boot & choose
        TFT_eSprite timeSprite = TFT_eSprite(&tft); //time & date
    
    public:
        LCDClass(void);
        void init_tft(void);
        void menu(Menu_screen_t screen, int y_pos);
        void swipe(Menu_screen_t screen, int y_pos);
        void slide(Menu_screen_t screen, int x_pos);
        void show_logo();
        void update_time(String time, String date);
        void set_rotation(uint8_t rotation);
        uint8_t get_rotation();
};

extern LCDClass lcd;

#endif // LCD_H_