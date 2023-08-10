#include <Arduino.h>
#include "system/vismate.h"
#include "device_config.h"
#include <HardwareSerial.h>
#include "sensor/MT6701.h"
#include <SPI.h>

HardwareSerial xiao(2);

#define MAIN_TAG "Main"
//21 TX, RX 14
unsigned long timeNow;
unsigned long timeUpdate;

SPIClass _magnetic_encoder;
MT6701_t enc(&_magnetic_encoder, 20);

void swipeUpScreen(){
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
}

void swipeDownScreen(){
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

    debugVal(MAIN_TAG, "Screen now : ", vismate.get_screen());
    debugVal(MAIN_TAG, "Last screen : ", vismate.get_last_screen());        
}

void click(){
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
    
    debugVal(MAIN_TAG, "Screen now : ", vismate.get_screen());
    debugVal(MAIN_TAG, "Last screen : ", vismate.get_last_screen());
        
}

void setup()
{
    Serial.begin(115200);
    xiao.begin(115200, SERIAL_8N1, 14, 21);
    // size_t psram_size = esp_spiram_get_size();
    // debugVal(MAIN_TAG, "PSRAM Size ",psram_size);

    vismate.setup_control();
    vismate.init_connection();
    vismate.init_lcd();
    vismate.speaker_test();
    delay(1000);
    lcd.update_time(ntp.get_time(), ntp.get_date());
    _magnetic_encoder.begin(48, 10, -1, 20);
    enc.Init();
    timeNow = millis();
}

void loop(){
    if (xiao.available()) {
        byte inByte = xiao.read();
        Serial.write(inByte);
    }

    if(millis() - timeNow > 1000){
        if(net.get_status()){
            debug(MAIN_TAG, "Connected");
        } else{
            debug(MAIN_TAG, "Disconnected");
        }
        enc.Sample();
        debugVal(MAIN_TAG, "Magn Sensor Angle : ", enc.GetAngle());
        debugVal(MAIN_TAG, "Magn Sensor Field : ", enc.GetField());
        debugVal(MAIN_TAG, "Magn Sensor Status : ", enc.GetStatus());
        debugVal(MAIN_TAG, "Magn Sensor Button : ", enc.GetButton());
        timeNow = millis();
    }

    if(millis() - timeUpdate > 30000){
        if(vismate.get_screen() == HOME_SCREEN){
            debug(MAIN_TAG, "Update");
            debugVal(MAIN_TAG, "Time now : ", ntp.get_time());
            debugVal(MAIN_TAG, "Date now : ", ntp.get_raw_date());
            lcd.update_time(ntp.get_time(), ntp.get_date());
        }
        timeUpdate = millis();
    }

    if(!digitalRead(16)){
        debug(MAIN_TAG, "Click");
        vTaskDelay(200 / portTICK_PERIOD_MS);
        if(!digitalRead(16)){
            debug(MAIN_TAG, "Hold");
            vTaskDelay(200 / portTICK_PERIOD_MS);
            if(!digitalRead(16)){
                debug(MAIN_TAG, "Long Hold");
                click();
                vTaskDelay(200 / portTICK_PERIOD_MS);
            } else{
                debug(MAIN_TAG, "Hold Release");
                swipeUpScreen();
                vTaskDelay(200 / portTICK_PERIOD_MS);
            }
        } else{
            debug(MAIN_TAG, "Release");
            swipeDownScreen();
            vTaskDelay(200 / portTICK_PERIOD_MS);
        }
    }
}
