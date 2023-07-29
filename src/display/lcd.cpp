#include "lcd.h"

LCDClass *lcd_instances;

LCDClass::LCDClass(void){

}

void LCDClass::init_tft(){
    lcd_instances = this;
    tft.init();
}

void LCDClass::boot(){
    tft.setRotation(3);
    tft.fillScreen(TFT_WHITE);
    tft.setPivot(120, 120);

    bgSprite.createSprite(230, 240);
    bgSprite.setSwapBytes(true);
    
    bgSprite.fillSprite(TFT_WHITE);
    bgSprite.pushImage(0, 0, 230, 230, org_logo);
    bgSprite.pushSprite(5, 5);

    delay(1500);

    bgSprite.fillSprite(TFT_WHITE);
    bgSprite.pushImage(0, 0, 230, 230, device_logo);
    bgSprite.pushSprite(5, 5);
}

void LCDClass::rotate(int rotation_state){
    tft.setRotation(rotation_state);
    _rotation_state = rotation_state;
}

void LCDClass::menu(Menu_screen_t screen, int y_pos){
    switch (screen) {

        case HOME_SCREEN:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, Home);
            bgSprite.pushSprite(5, y_pos+5);
            break;
        case NOTES:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, notes_icon);
            bgSprite.pushSprite(5, y_pos+5);
            break;
        case SPEECH:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, speech_icon);
            bgSprite.pushSprite(5, y_pos+5);
            break;
        case NAVIGATION:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, navi_icon);
            bgSprite.pushSprite(5, y_pos+5);
            break;
        case MAPS:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, maps_icon);
            bgSprite.pushSprite(5, y_pos+5);
            break;
        case SETTING:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, setting_icon);
            bgSprite.pushSprite(5, y_pos+5);
            break;
        default:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, Home);
            bgSprite.pushSprite(5, y_pos+5);
            break;
    }
}

LCDClass lcd;