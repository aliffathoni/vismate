#include <Arduino.h>
#include "system/vismate.h"
#include "device_config.h"
#include <HardwareSerial.h>
#include "AiEsp32RotaryEncoder.h"
#include "Adafruit_VL53L0X.h"
#include "driver/rtc_io.h"

TwoWire *TOF_I2C;

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(19, 20, 48, -1, 4);

HardwareSerial xiao(2);

int position = 0;

bool updateTof = false;

#define MAIN_TAG "Main"
//21 TX, RX 14
unsigned long timeNow;
unsigned long timeUpdate;
unsigned long tofUpdate;

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

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
    rtc_gpio_deinit(GPIO_NUM_16);

    vismate.init_lcd();

    print_wakeup_reason();
    vismate.setup_control();
    vismate.init_connection();
    
    rtc_gpio_deinit(GPIO_NUM_11);
    rtc_gpio_deinit(GPIO_NUM_12);
    rtc_gpio_deinit(GPIO_NUM_15);
    rtc_gpio_deinit(GPIO_NUM_17);
    rtc_gpio_deinit(GPIO_NUM_18);

    lcd.init_tft();
    lcd.show_device_logo();
    // vismate.init_lcd();
    
    lox.begin();
    lox.configSensor(lox.VL53L0X_SENSE_LONG_RANGE);
    
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

    if((millis() - tofUpdate > 250) && (updateTof)){
        VL53L0X_RangingMeasurementData_t measure;
    
        Serial.print("Reading a measurement... ");
        lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

        if (measure.RangeStatus != 4) {  // phase failures have incorrect data
            Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
        } else {
            Serial.println(" out of range ");
        }

        tofUpdate = millis();
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
        debug(MAIN_TAG, "Sleep mode...");
        vTaskDelay(2000 / portTICK_PERIOD_MS);

        rtc_gpio_pullup_en(GPIO_NUM_16);
        esp_sleep_enable_ext0_wakeup(GPIO_NUM_16, LOW);
        esp_deep_sleep_start();
    }
}
