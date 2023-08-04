#include "lcd.h"

LCDClass *lcd_instances;

LCDClass::LCDClass(void){

}

void LCDClass::init_tft(){
    lcd_instances = this;
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_WHITE);
    // tft.setFreeFont(&FreeSans18pt7b);
    tft.setTextDatum(CC_DATUM);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    // tft.drawString("Loading123", 120, 120, 4); //small
    // delay(1000);
    // tft.fillScreen(TFT_WHITE);
    // tft.drawString("Loading 6", 120, 120, 6); //big
    // delay(1000);
    // tft.fillScreen(TFT_WHITE);
    // tft.drawString("Loading 7", 120, 120, 7); //watch

    bgSprite.createSprite(240, 240);
    bgSprite.setSwapBytes(true);

    textSprite.createSprite(240, 240);

    iconSprite.createSprite(50, 50);
    iconSprite.setSwapBytes(true);
}

void LCDClass::show_logo(){
    tft.setRotation(3);
    tft.fillScreen(TFT_WHITE);
    tft.setPivot(120, 120);

    bgSprite.createSprite(240, 240);
    bgSprite.setSwapBytes(true);
    
    bgSprite.fillSprite(TFT_WHITE);
    bgSprite.pushImage(0, 0, 230, 230, org_logo);
    bgSprite.pushSprite(5, 5);

    delay(1500);

    bgSprite.fillSprite(TFT_WHITE);
    bgSprite.pushImage(0, 0, 230, 230, device_logo);
    bgSprite.pushSprite(5, 5);
}

void LCDClass::swipe(Menu_screen_t screen, int y_pos){
    switch (screen) {
        case HOME_SCREEN:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, Home);
            bgSprite.pushSprite(0, y_pos+5);
            break;
        case NOTES:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 0, 230, 230, notes_icon);
            bgSprite.pushSprite(0, y_pos+5);
            break;
        case SPEAK:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 0, 230, 230, speech_icon);
            bgSprite.pushSprite(0, y_pos+5);
            break;
        case NAVIGATION:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 0, 230, 230, navi_icon);
            bgSprite.pushSprite(0, y_pos+5);
            break;
        case MAPS:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 0, 230, 230, maps_icon);
            bgSprite.pushSprite(0, y_pos+5);
            break;
        case SETTING:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 0, 230, 230, setting_icon);
            bgSprite.pushSprite(0, y_pos+5);
            break;
        
        default:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, Home);
            bgSprite.pushSprite(5, y_pos+5);
            break;
    }
}

void LCDClass::slide(Menu_screen_t screen, int x_pos){
    switch (screen) {
        case HOME_MAPS:
            bgSprite.fillSprite(TFT_WHITE);
            iconSprite.fillSprite(TFT_WHITE);
            iconSprite.pushImage(0, 0, 50, 50, choose_maps);
            iconSprite.pushToSprite(&bgSprite, 40, 95);
            
            textSprite.fillSprite(TFT_WHITE);
            textSprite.setFreeFont(&FreeSans12pt7b);
            textSprite.setTextDatum(CL_DATUM);
            textSprite.setTextColor(TFT_BLACK, TFT_WHITE);
            textSprite.drawString("Brawijaya", 95, 120);
            textSprite.pushToSprite(&bgSprite, 0, 0, TFT_WHITE);
            
            bgSprite.pushSprite(x_pos, 0);
            break;
        case SHOW_MAPS:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 5, 230, 230, map_ub);
            bgSprite.pushSprite(x_pos+5, 0);
            break;

        case LISTENING:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, listening);
            bgSprite.pushSprite(x_pos+5, 5);
            break;

        case LOADING:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, loading);
            bgSprite.pushSprite(x_pos+5, 5);
            break;
        
        default:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, Home);
            bgSprite.pushSprite(x_pos+5, 5);
            break;
    }

}

void LCDClass::update_time(String time, String date){
    timeSprite.fillSprite(TFT_WHITE);
    timeSprite.setTextDatum(TR_DATUM);
    timeSprite.setTextColor(TFT_BLACK, TFT_WHITE);
    timeSprite.drawString("88:88", 205, 35, 7);

    timeSprite.setTextDatum(TR_DATUM);
    timeSprite.setTextColor(TFT_BLACK, TFT_WHITE);
    timeSprite.drawString("SUN 30", 200, 100, 4);
    timeSprite.pushSprite(0, 0, TFT_WHITE);
}

void LCDClass::set_rotation(uint8_t rotation){
    tft.setRotation(rotation);
}

uint8_t LCDClass::get_rotation(){
    return tft.getRotation();
}

LCDClass lcd;