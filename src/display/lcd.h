#ifndef LCD_H_
#define LCD_H_

#include <Arduino.h>

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#include "../device_config.h"
#include "Image.h"

// typedef void (*CallBacFunc) (Menu_State_t);

class LCDClass {
    private:
        TFT_eSPI tft = TFT_eSPI();
        TFT_eSprite bgSprite = TFT_eSprite(&tft);
        TFT_eSprite iconSprite = TFT_eSprite(&tft);

        int _rotation_state;
    
    public:
        LCDClass(void);
        void init_tft(void);
        void menu(Menu_screen_t screen, int y_pos);
        // void moveTo(int menu, int y_pos);
        // void backTo(int menu, int y_pos);
        void rotate(int rotation_state);
        void boot();
        // void connect(bool connection_status);
        // void showServer();
};

extern LCDClass lcd;

#endif // LCD_H_