#include <Arduino.h>
#include "system/vismate.h"
#include "device_config.h"
#include <HardwareSerial.h>
#include "AiEsp32RotaryEncoder.h"

#define ROTARY_ENCODER_A_PIN 19
#define ROTARY_ENCODER_B_PIN 20
#define ROTARY_ENCODER_BUTTON_PIN 48
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

HardwareSerial xiao(2);

int position = 0;

#define MAIN_TAG "Main"
//21 TX, RX 14
unsigned long timeNow;
unsigned long timeUpdate;

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
    static unsigned long lastTimePressed = 0; // Soft debouncing
    if (millis() - lastTimePressed < 100){
        return;
    }
    lastTimePressed = millis();

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

void IRAM_ATTR rotary_isr()
{
    rotaryEncoder.readEncoder_ISR();
}

void control_loop(){
    if(rotaryEncoder.encoderChanged()){
        int buff = rotaryEncoder.readEncoder();

        if(buff > position){
            position = buff;
            swipeDownScreen();
        } else if(buff < position){
            position = buff;
            swipeUpScreen();
        }
    }

    if (rotaryEncoder.isEncoderButtonClicked()){
        debug(MAIN_TAG, "clicked");
        click();
    }
}

void setup()
{
    Serial.begin(115200);
    xiao.begin(115200, SERIAL_8N1, 14, 21);
    delay(1000);

    vismate.setup_control();
    vismate.init_connection();
    vismate.init_lcd();
    vismate.speaker_test();
    delay(1000);
    lcd.update_time(ntp.get_time(), ntp.get_date());
    timeNow = millis();

    rotaryEncoder.begin();
    rotaryEncoder.setup(rotary_isr);
    rotaryEncoder.setBoundaries(-100, 100, false);
    rotaryEncoder.disableAcceleration();
    rotaryEncoder.setEncoderValue(0);
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

    control_loop();

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
