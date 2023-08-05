#include <Arduino.h>
#include "system/vismate.h"
#include "device_config.h"

#define MAIN_TAG "Main"

unsigned long timeNow;

void setup()
{
    Serial.begin(115200);
    
    // size_t psram_size = esp_spiram_get_size();
    // debugVal(MAIN_TAG, "PSRAM Size ",psram_size);

    vismate.setup_control();
    vismate.init_connection();
    vismate.init_lcd();
    vismate.speaker_test();
    delay(1000);
    vismate.screen(HOME_SCREEN);
    timeNow = millis();
}

void loop(){
    if(millis() - timeNow > 1000){
        if(net.get_status()){
            debug(MAIN_TAG, "Connected");
        } else{
            debug(MAIN_TAG, "Disconnected");
        }

        if(vismate.get_screen() == HOME_SCREEN){
            lcd.update_time("23:59", "SUN30");
            debug(MAIN_TAG, "Update");
        }
        timeNow = millis();
    }

    if(!digitalRead(16)){
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
        
        debugVal(MAIN_TAG, "Screen now : ", vismate.get_screen());
        debugVal(MAIN_TAG, "Last screen : ", vismate.get_last_screen());
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }

    // if(!digitalRead(10)){
    //   switch (vismate.get_screen()){
    //     case SETTING:
    //         vismate.screen(HOME_SCREEN);
    //         break;
    //     case MAPS:
    //         vismate.screen(SETTING);
    //         break;
    //     case NAVIGATION:
    //         vismate.screen(MAPS);
    //         break;
    //     case SPEAK:
    //         vismate.screen(NAVIGATION);
    //         break;
    //     case NOTES:
    //         vismate.screen(SPEAK);
    //         break;
    //     case HOME_SCREEN:
    //         vismate.screen(NOTES);
    //         break;
    //     case HOME_MAPS:
    //         vismate.screen(MAPS);
    //         break;
    //     case SHOW_MAPS:
    //         vismate.screen(MAPS);
    //         break;
    //     case LOADING:
    //         vismate.screen(NOTES);
    //         break;
    //     default:
    //         vismate.screen(vismate.get_last_screen());
    //         break;
    //     }

    //     debugVal(MAIN_TAG, "Screen now : ", vismate.get_screen());
    //     debugVal(MAIN_TAG, "Last screen : ", vismate.get_last_screen());
    //     vTaskDelay(200 / portTICK_PERIOD_MS);
    // }

    // if(!digitalRead(9)){
    //     switch (vismate.get_screen()){
    //         case MAPS:
    //             vismate.screen(HOME_MAPS);
    //             break;
    //         case HOME_MAPS:
    //             vismate.screen(SHOW_MAPS);
    //             break;
    //         case SHOW_MAPS:
    //             vismate.screen(MAPS);
    //             break;
    //         case NOTES:
    //             vismate.screen(LISTENING);
    //             break;
    //         case LISTENING:
    //             vismate.screen(LOADING);
    //             break;
    //         case LOADING:
    //             vismate.screen(NOTES);
    //             break;
    //         default:
    //             vismate.screen(vismate.get_last_screen());
    //             break;
    //     }
        
    //     debugVal(MAIN_TAG, "Screen now : ", vismate.get_screen());
    //     debugVal(MAIN_TAG, "Last screen : ", vismate.get_last_screen());
    //     vTaskDelay(200 / portTICK_PERIOD_MS);
    // }
}
