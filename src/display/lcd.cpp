#include "lcd.h"

LCDClass *lcd_instances;

LCDClass::LCDClass(void){

}

void LCDClass::init_tft(){
    lcd_instances = this;
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_WHITE);
    tft.setTextDatum(CC_DATUM);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setPivot(120, 120);

    bgSprite.createSprite(240, 240);
    bgSprite.setSwapBytes(true);

    textSprite.createSprite(100, 150);

    iconSprite.createSprite(50, 50);
#ifdef LCD_DEBUG
    debug(LCD_TAG, "Init LCD");
#endif
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
#ifdef LCD_DEBUG
    debug(LCD_TAG, "Show Logo");
#endif
}

void LCDClass::swipe(Menu_screen_t screen, int y_pos){
    switch (screen) {
        case HOME_SCREEN:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, Home);
            bgSprite.pushSprite(0, y_pos+5);
#ifdef LCD_DEBUG
            debug(LCD_TAG, "Swipe Home");
#endif            
            break;
        case NOTES:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 0, 230, 230, notes_icon);
            bgSprite.pushSprite(0, y_pos+5);
#ifdef LCD_DEBUG
            debug(LCD_TAG, "Swipe Notes");
#endif
            break;
        case SPEAK:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 0, 230, 230, speech_icon);
            bgSprite.pushSprite(0, y_pos+5);
#ifdef LCD_DEBUG
            debug(LCD_TAG, "Swipe Speech");
#endif
            break;
        case NAVIGATION:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 0, 230, 230, navi_icon);
            bgSprite.pushSprite(0, y_pos+5);
#ifdef LCD_DEBUG            
            debug(LCD_TAG, "Swipe Navigation");
#endif
            break;
        case MAPS:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 0, 230, 230, maps_icon);
            bgSprite.pushSprite(0, y_pos+5);
#ifdef LCD_DEBUG
            debug(LCD_TAG, "Swipe Maps");
#endif            
            break;
        case SETTING:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 0, 230, 230, setting_icon);
            bgSprite.pushSprite(0, y_pos+5);
#ifdef LCD_DEBUG
            debug(LCD_TAG, "Swipe Setting");
#endif
            break;
        
        default:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, Home);
            bgSprite.pushSprite(5, y_pos+5);
#ifdef LCD_DEBUG
            debug(LCD_TAG, "Swipe Default");
#endif
            break;
    }
}

void LCDClass::slide(Menu_screen_t screen, int x_pos){
    switch (screen) {
        case NOTES:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 0, 230, 230, notes_icon);
            bgSprite.pushSprite(x_pos+5, 5);
#ifdef LCD_DEBUG
            debug(LCD_TAG, "Slide Notes");
#endif
            break;
        case SPEAK:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 0, 230, 230, speech_icon);
            bgSprite.pushSprite(x_pos+5, 5);
#ifdef LCD_DEBUG
            debug(LCD_TAG, "Slide Speech");
#endif
            break;
        case NAVIGATION:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 0, 230, 230, navi_icon);
            bgSprite.pushSprite(x_pos+5, 5);
#ifdef LCD_DEBUG
            debug(LCD_TAG, "Slide Navigation");
#endif
            break;
        case MAPS:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 0, 230, 230, maps_icon);
            bgSprite.pushSprite(x_pos+5, 5);
#ifdef LCD_DEBUG
            debug(LCD_TAG, "Slide Maps");
#endif
            break;
        case SETTING:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(5, 0, 230, 230, setting_icon);
            bgSprite.pushSprite(x_pos+5, 5);
#ifdef LCD_DEBUG
            debug(LCD_TAG, "Slide Setting");
#endif
            break;
        case HOME_MAPS:
            bgSprite.fillSprite(TFT_WHITE);
            iconSprite.fillSprite(TFT_WHITE);
            
            iconSprite.fillSprite(TFT_WHITE);
            iconSprite.pushImage(0, 0, 50, 50, choose_maps);
            iconSprite.pushToSprite(&bgSprite, 40, 95, TFT_WHITE);
            
            bgSprite.setTextDatum(CL_DATUM);
            bgSprite.setFreeFont(&FreeSans12pt7b);
            bgSprite.setTextColor(TFT_BLACK, TFT_WHITE);
            bgSprite.drawString("Brawijaya", 95, 130);

            bgSprite.setTextDatum(TC_DATUM);
            bgSprite.setFreeFont(&FreeSans9pt7b);
            bgSprite.drawString("Home", 120, 150);

            bgSprite.pushSprite(x_pos, 0);

#ifdef LCD_DEBUG
            debug(LCD_TAG, "Slide Choose Maps");
#endif
            break;
        case SHOW_MAPS:
            bgSprite.fillSprite(TFT_NAVY);
            bgSprite.pushImage(1, 1, 238, 238, map_ub);
            bgSprite.pushSprite(x_pos, 0);
#ifdef LCD_DEBUG
            debug(LCD_TAG, "Slide Home Maps");
#endif
            break;

        case LISTENING:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, listening);
            bgSprite.pushSprite(x_pos+5, 5);
#ifdef LCD_DEBUG
            debug(LCD_TAG, "Slide Listening");
#endif
            break;

        case LOADING:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, loading);
            bgSprite.pushSprite(x_pos+5, 5);
#ifdef LCD_DEBUG
            debug(LCD_TAG, "Slide Loading");
#endif
            break;
        
        default:
            bgSprite.fillSprite(TFT_WHITE);
            bgSprite.pushImage(0, 0, 230, 230, Home);
            bgSprite.pushSprite(x_pos+5, 5);
#ifdef LCD_DEBUG
            debug(LCD_TAG, "Slide Default");
#endif
            break;
    }

}

void LCDClass::update_time(String time, String date){
    bgSprite.fillSprite(TFT_WHITE);
    bgSprite.pushImage(0, 0, 230, 230, Home);
    bgSprite.setTextDatum(TR_DATUM);
    bgSprite.setTextColor(TFT_BLACK);
    bgSprite.drawString(time, 205, 35, 7);
    bgSprite.drawString(date, 200, 100, 4);
    bgSprite.pushSprite(0, 5);
}

void LCDClass::set_rotation(uint8_t rotation){
    tft.setRotation(rotation);
}

uint8_t LCDClass::get_rotation(){
    return tft.getRotation();
}

LCDClass lcd;