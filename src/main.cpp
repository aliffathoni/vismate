#include <Arduino.h>
#include "system/vismate.h"
#include "device_config.h"

#define MAIN_TAG "Main"

void setup()
{
    Serial.begin(115200);
    
    size_t psram_size = esp_spiram_get_size();
    debugVal(MAIN_TAG, "PSRAM Size ",psram_size);

    vismate.setup_control();
    vismate.init_lcd();
    vismate.init_connection();
    // vismate.speaker_test();
    vismate.set_volume(0);
    delay(1000);
    vismate.screen(HOME_SCREEN);
}

void loop(){
    if(!digitalRead(3)){
      switch (vismate.get_screen()){
        case HOME_SCREEN:
            vismate.screen(SETTING);
            break;
        case SETTING:
            vismate.screen(MAPS);
            break;
        case MAPS:
            vismate.screen(NAVIGATION);
            break;
        case NAVIGATION:
            vismate.screen(SPEAK);
            break;
        case SPEAK:
            vismate.screen(NOTES);
            break;
        case NOTES:
            vismate.screen(HOME_SCREEN);
            break;


        case HOME_MAPS:
            vismate.screen(MAPS);
            break;
        case SHOW_MAPS:
            vismate.screen(MAPS);
            break;
        case LOADING:
            vismate.screen(NOTES);
            break;
        default:
            vismate.screen(vismate.get_last_screen());
            break;
      }
        debugVal(MAIN_TAG, "Screen change : ", vismate.get_screen());
      vTaskDelay(200 / portTICK_PERIOD_MS);
    }

    if(!digitalRead(10)){
      switch (vismate.get_screen()){
        case SETTING:
            vismate.screen(HOME_SCREEN);
            break;
        case MAPS:
            vismate.screen(SETTING);
            break;
        case NAVIGATION:
            vismate.screen(MAPS);
            break;
        case SPEAK:
            vismate.screen(NAVIGATION);
            break;
        case NOTES:
            vismate.screen(SPEAK);
            break;
        case HOME_SCREEN:
            vismate.screen(NOTES);
            break;
        case HOME_MAPS:
            vismate.screen(MAPS);
            break;
        case SHOW_MAPS:
            vismate.screen(MAPS);
            break;
        case LOADING:
            vismate.screen(NOTES);
            break;
        default:
            vismate.screen(vismate.get_last_screen());
            break;
      }
        debugVal(MAIN_TAG, "Screen change : ", vismate.get_screen());
      vTaskDelay(200 / portTICK_PERIOD_MS);
    }

    if(!digitalRead(9)){
        switch (vismate.get_screen()){
            case MAPS:
                vismate.screen(HOME_MAPS);
                break;
            case HOME_MAPS:
                vismate.screen(SHOW_MAPS);
                break;
            case SHOW_MAPS:
                vismate.screen(MAPS);
                break;
            case NOTES:
                vismate.screen(LISTENING);
                break;
            case LISTENING:
                vismate.screen(LOADING);
                break;
            case LOADING:
                vismate.screen(NOTES);
                break;
            default:
                vismate.screen(vismate.get_last_screen());
                break;
        }
        debugVal(MAIN_TAG, "Screen change : ", vismate.get_screen());
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}
