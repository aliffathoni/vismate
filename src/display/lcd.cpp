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
    // iconSprite.createSprite(130, 240);
    // iconSprite.setSwapBytes(true);
    // iconSprite.fillSprite(TFT_WHITE);
    // iconSprite.pushImage(0, 0, 130, 130, Logo);
    // iconSprite.pushSprite(55, 55);

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

void LCDClass::menu(int menu, int y_pos){
    if(menu == 0){
        bgSprite.fillSprite(TFT_WHITE);
        bgSprite.pushImage(0, 0, 230, 230, Home);
        bgSprite.pushSprite(5, y_pos+5);
    } else if(menu == 1){
        bgSprite.fillSprite(TFT_WHITE);
        bgSprite.pushImage(0, 0, 230, 230, notes_icon);
        bgSprite.pushSprite(5, y_pos+5);
    } else if(menu == 2){
        bgSprite.fillSprite(TFT_WHITE);
        bgSprite.pushImage(0, 0, 230, 230, speech_icon);
        bgSprite.pushSprite(5, y_pos+5);
    } else if(menu == 3){
        bgSprite.fillSprite(TFT_WHITE);
        bgSprite.pushImage(0, 0, 230, 230, navi_icon);
        bgSprite.pushSprite(5, y_pos+5);
    } else if(menu == 4){
        bgSprite.fillSprite(TFT_WHITE);
        bgSprite.pushImage(0, 0, 230, 230, maps_icon);
        bgSprite.pushSprite(5, y_pos+5);
    } else if(menu == 5){
        bgSprite.fillSprite(TFT_WHITE);
        bgSprite.pushImage(0, 0, 230, 230, setting_icon);
        bgSprite.pushSprite(5, y_pos+5);
    }
}

LCDClass lcd;