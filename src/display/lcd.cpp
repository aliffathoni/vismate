#include "lcd.h"

LCDClass *lcd_instances;

LCDClass::LCDClass(void){
    lcd_instances = this;
}

void LCDClass::init_tft(){
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_WHITE);
    tft.setTextDatum(CC_DATUM);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setPivot(120, 120);

    mainBg.createSprite(240, 240);
    mainBg.setSwapBytes(true);

    bgSprite.createSprite(240, 240);
    bgSprite.setSwapBytes(true);

    textSprite.createSprite(100, 150);
    textSprite.setSwapBytes(true);

    iconSprite.createSprite(50, 50);
    iconSprite.setSwapBytes(true);
}

void LCDClass::show_logo(){    
    mainBg.fillSprite(TFT_WHITE);
    bgSprite.fillSprite(TFT_WHITE);
    bgSprite.pushImage(1, 1, 238, 238, _org_logo);
    bgSprite.pushToSprite(&mainBg, 0, 0);
    mainBg.pushSprite(0, 0);

    delay(1500);
}

void LCDClass::show_device_logo(){
    mainBg.fillSprite(TFT_WHITE);
    bgSprite.fillSprite(TFT_WHITE);
    bgSprite.pushImage(1, 1, 238, 238, device_logo);
    bgSprite.pushToSprite(&mainBg, 0, 0);
    mainBg.pushSprite(0, 0);
}

void LCDClass::update_time(String time, String date, int batt){
    mainBg.fillSprite(TFT_WHITE);
    bgSprite.fillSprite(TFT_WHITE);
    bgSprite.pushImage(1, 1, 238, 238, home_screen);
    bgSprite.setTextDatum(TR_DATUM);
    bgSprite.setTextColor(TFT_BLACK);
    if(batt > 80){
        bgSprite.pushImage(107, 3, 25, 15, battery_full);
    } else if(batt > 30 && batt <= 80){
        bgSprite.pushImage(107, 3, 25, 15, battery_half);
    } else{
        bgSprite.pushImage(107, 3, 25, 15, battery_low);
    }
    bgSprite.drawString(time, 205, 40, 7);
    bgSprite.drawString(date, 200, 105, 4);
    bgSprite.pushRotated(&mainBg, _rotate_angle);
    mainBg.pushSprite(0, 0);
}

void LCDClass::moveTo(Menu_screen_t screen_name, int x_pos, int y_pos, uint16_t rotate_angle){
    mainBg.fillSprite(TFT_WHITE);
    _rotate_angle = rotate_angle;
    switch(screen_name) {        
        case HOME_SCREEN:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, home_screen);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
        case NOTES:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, note_screen);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
        case SPEAK:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, speech_screen);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
        case NAVIGATION:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, navi_screen);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
        case MAPS:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, maps_screen);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
        case SETTING:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, setting_screen);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
        case LISTENING:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, note_screen);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
        case SPEAK_SAVED_PHRASE:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, text_to_speech);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
        case OBJECT_DETECTION:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, navi_screen);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
        case UNIV_MAPS:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, maps_ub);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
        case SET_VOLUME:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, setting_speaker);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
        case SET_TIMEOUT:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, setting_timeout);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
        case INFO_WIFI:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, setting_wifi);
            bgSprite.setTextDatum(CC_DATUM);
            bgSprite.setTextColor(TFT_BLACK);
            bgSprite.drawString("Connected with", x_pos+120, y_pos+150, 1);
            bgSprite.drawString(_string_buff, x_pos+120, y_pos+170, 4);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
        case SETTING_BACK:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, back);
            bgSprite.setTextDatum(CC_DATUM);
            bgSprite.setTextColor(TFT_BLACK);
            bgSprite.drawString("Back", x_pos+120, y_pos+170, 4);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
        case REBOOT:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, setting_reboot);
            bgSprite.setTextDatum(CC_DATUM);
            bgSprite.setTextColor(TFT_BLACK);
            bgSprite.drawString("Reboot", x_pos+120, y_pos+170, 4);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
        default:
            bgSprite.pushImage(x_pos+1, y_pos+1, 238, 238, home_screen);
            bgSprite.pushRotated(&mainBg, rotate_angle);
            break;
    }
    mainBg.pushSprite(0, 0);
}

void LCDClass::load(int progress, int rotate_angle){
    bgSprite.fillSmoothRoundRect(70, 150, 100, 15, 15, TFT_DARKGREY, TFT_WHITE);
    bgSprite.fillSmoothRoundRect(70, 150, 10*progress, 15, 15, TFT_BLUE, TFT_WHITE);
    bgSprite.pushRotated(&mainBg, rotate_angle);
    mainBg.pushSprite(0, 0);
}

void LCDClass::set_rotation(uint8_t rotation){
    tft.setRotation(rotation);
}

uint8_t LCDClass::get_rotation(){
    return tft.getRotation();
}

LCDClass lcd;