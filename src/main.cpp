#include <Arduino.h>
#include "system/vismate.h"

HardwareSerial xiao = Serial2;

int position = 0;

String _obj_buff;
String _url_buff;

bool new_obj = false;
bool updateTof = false;
bool sleepMode = false;

#define MAIN_TAG "Main"
//21 TX, RX 14

unsigned long screenTimeOut = 30000;
uint8_t vol_buff = 21;

unsigned long tofUpdate;
unsigned long sleepCheck;
unsigned long battCheck;
unsigned long blControl;

void receiverCallback(){
  String _buff = "";
  _url_buff = "";
  while(xiao.available()){
    char c = xiao.read();
    _buff+=c;
  }
  
  DynamicJsonDocument  doc(200);
  DeserializationError error = deserializeJson(doc, _buff);

  // Test if parsing succeeds.
  if (error) {
    debugVal(MAIN_TAG, "deserializeJson() failed: ", error.f_str());

    return;
  }
  
  const char* obj = doc["object"];
  const char* url = doc["url"];
  _obj_buff = obj;
  _url_buff = url;
  new_obj = true;
  debugVal(MAIN_TAG, "Received object : ", obj);
}

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

void sleepTask(void *param){
    unsigned long button_hold;
    while(1){
        if(millis() - blControl > screenTimeOut){
            digitalWrite(TFT_BL, LOW);
            blControl = millis();
        }
        if(sleepMode){
            debug(MAIN_TAG, "Sleep mode...");
            voice.speak("Sleeping in two second");
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            
            digitalWrite(TFT_BL, LOW);
            rtc_gpio_hold_en(GPIO_NUM_15);
            rtc_gpio_pullup_en(GPIO_NUM_16);
            esp_sleep_enable_ext0_wakeup(GPIO_NUM_16, LOW);
            esp_deep_sleep_start();
        }
        
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

void connectionTask(void *param){
    while(1){
        if(!voice.isRunning() && sleepMode == false){
            if(net.get_status()){
                debug(MAIN_TAG, "Connected");
            } else{
                debug(MAIN_TAG, "Disconnected");
            }

            int batt_percentage = battery.get_percentage();
            debugVal(MAIN_TAG, "Battery : ", batt_percentage);

            if(batt_percentage < 15) voice.speak("Battery low");
            debugVal(MAIN_TAG, "Send data...", fb.set(batt_percentage, "Data/LNwCMmoksbSaT51dIjv83rvHp1j1/Batt"));
            
            if(vismate.get_screen() == HOME_SCREEN){
                debug(MAIN_TAG, "Update");
                debugVal(MAIN_TAG, "Time now : ", ntp.get_time());
                debugVal(MAIN_TAG, "Date now : ", ntp.get_raw_date());
                lcd.update_time(ntp.get_time(), ntp.get_date(), batt_percentage);
            }
        }
        vTaskDelay(15000 / portTICK_PERIOD_MS);
    }
}

void IRAM_ATTR rotary_isr(){
    enc.readEncoder();
}

void IRAM_ATTR sleep_isr(){
    sleepMode = true;
}

void controlTask(void *param){
    int current_pos = 0;
    int last_pos = 0;
    int angle = 0;

    Menu_screen_t main_screen;
    while(1){
        if(!voice.isRunning() && sleepMode == false){
            enc.read();
            if(enc.isChanged()){
                digitalWrite(TFT_BL, HIGH);
                current_pos = enc.position();
                debugVal(MAIN_TAG, "Position : ", current_pos);
                debugVal(MAIN_TAG, "Direction : ", enc.direction());
                if(current_pos < 6 && current_pos > -6 && vismate.get_screen() < 6){
                    if(enc.direction() == 1){
                        angle -= 18;        
                        switch(vismate.get_screen()){
                            case HOME_SCREEN :
                                for(int x = 0; x <= 240; x+=40){
                                    lcd.moveTo(HOME_SCREEN, x, 0, angle);
                                    lcd.moveTo(SETTING, x-240, 0, angle);
                                }
                                vismate.setScreen(SETTING);
                                break;
                            case SETTING :
                                for(int x = 0; x <= 240; x+=40){
                                    lcd.moveTo(SETTING, x, 0, angle);
                                    lcd.moveTo(MAPS, x-240, 0, angle);
                                }
                                vismate.setScreen(MAPS);
                                break;
                            case MAPS :
                                for(int x = 0; x <= 240; x+=40){
                                    lcd.moveTo(MAPS, x, 0, angle);
                                    lcd.moveTo(NAVIGATION, x-240, 0, angle);
                                }
                                vismate.setScreen(NAVIGATION);
                                break;
                            case NAVIGATION :
                                for(int x = 0; x <= 240; x+=40){
                                    lcd.moveTo(NAVIGATION, x, 0, angle);
                                    lcd.moveTo(SPEAK, x-240, 0, angle);
                                }
                                vismate.setScreen(SPEAK);
                                break;
                            case SPEAK :
                                for(int x = 0; x <= 240; x+=40){
                                    lcd.moveTo(SPEAK, x, 0, angle);
                                    lcd.moveTo(NOTES, x-240, 0, angle);
                                }
                                vismate.setScreen(NOTES);
                                break;
                            case NOTES :
                                for(int x = 0; x <= 240; x+=40){
                                    lcd.moveTo(NOTES, x, 0, angle);
                                    lcd.moveTo(HOME_SCREEN, x-240, 0, angle);
                                }
                                lcd.update_time(ntp.get_time(), ntp.get_date(), battery.get_percentage());
                                vismate.setScreen(HOME_SCREEN);
                                break;
                            }
                        
                    } else if(enc.direction() == -1){
                        angle += 18;
                        switch(vismate.get_screen()){
                            case HOME_SCREEN :
                                for(int x = 240; x >= 0; x-=40){
                                    lcd.moveTo(HOME_SCREEN, x-240, 0, angle);
                                    lcd.moveTo(NOTES, x, 0, angle);
                                }
                                vismate.setScreen(NOTES);
                                break;
                            case NOTES :
                                for(int x = 240; x >= 0; x-=40){
                                    lcd.moveTo(NOTES, x-240, 0, angle);
                                    lcd.moveTo(SPEAK, x, 0, angle);
                                }
                                vismate.setScreen(SPEAK);
                                break;
                            case SPEAK :
                                for(int x = 240; x >= 0; x-=40){
                                    lcd.moveTo(SPEAK, x-240, 0, angle);
                                    lcd.moveTo(NAVIGATION, x, 0, angle);
                                }
                                vismate.setScreen(NAVIGATION);
                                break;
                            case NAVIGATION :
                                for(int x = 240; x >= 0; x-=40){
                                    lcd.moveTo(NAVIGATION, x-240, 0, angle);
                                    lcd.moveTo(MAPS, x, 0, angle);
                                }
                                vismate.setScreen(MAPS);
                                break;
                            case MAPS :
                                for(int x = 240; x >= 0; x-=40){
                                    lcd.moveTo(MAPS, x-240, 0, angle);
                                    lcd.moveTo(SETTING, x, 0, angle);
                                }
                                vismate.setScreen(SETTING);
                                break;
                            case SETTING :
                                for(int x = 240; x >= 0; x-=40){
                                    lcd.moveTo(SETTING, x-240, 0, angle);
                                    lcd.moveTo(HOME_SCREEN, x, 0, angle);
                                }
                                lcd.update_time(ntp.get_time(), ntp.get_date(), battery.get_percentage());
                                vismate.setScreen(HOME_SCREEN);
                                break;
                        }
                    }

                    vismate.talk(vismate.get_screen());
                    main_screen = vismate.get_screen();
                    debugVal(MAIN_TAG, "Main screen : ", main_screen);
                } else if(vismate.get_screen() < 6){
                    int fix_position = enc.position() > 5 ? 5 : -5;
                    enc.setPosition(fix_position);
                    debugVal(MAIN_TAG, "Fix position to ", fix_position);
                    voice.speak("This is the last position available");
                }

                if(vismate.get_screen() >= 18){
                    if(enc.direction() == 1){
                        angle -= 18;        
                        switch(vismate.get_screen()){
                            case SET_VOLUME :
                                for(int x = 0; x <= 240; x+=40){
                                    lcd.moveTo(SET_VOLUME, x, 0, angle);
                                    lcd.moveTo(SET_TIMEOUT, x-240, 0, angle);
                                }
                                lcd.load(screenTimeOut/6000, angle);
                                voice.speak("Screen Timeout");
                                vismate.setScreen(SET_TIMEOUT);
                                break;
                            case SET_TIMEOUT :
                                for(int x = 0; x <= 240; x+=40){
                                    lcd.moveTo(SET_TIMEOUT, x, 0, angle);
                                    lcd.moveTo(INFO_WIFI, x-240, 0, angle);
                                }
                                voice.speak("WiFi Information");
                                vismate.setScreen(INFO_WIFI);
                                break;
                            case INFO_WIFI :
                                for(int x = 0; x <= 240; x+=40){
                                    lcd.moveTo(INFO_WIFI, x, 0, angle);
                                    lcd.moveTo(REBOOT, x-240, 0, angle);
                                }
                                voice.speak("Restart device");
                                vismate.setScreen(REBOOT);
                                break;
                            case REBOOT :
                                for(int x = 0; x <= 240; x+=40){
                                    lcd.moveTo(REBOOT, x, 0, angle);
                                    lcd.moveTo(SETTING_BACK, x-240, 0, angle);
                                }
                                voice.speak("Back to menu");
                                vismate.setScreen(SETTING_BACK);
                                break;
                            case SETTING_BACK :
                                for(int x = 0; x <= 240; x+=40){
                                    lcd.moveTo(SETTING_BACK, x, 0, angle);
                                    lcd.moveTo(SET_VOLUME, x-240, 0, angle);
                                }
                                lcd.load((vol_buff*10)/21, angle);
                                voice.speak("Set Volume");
                                vismate.setScreen(SET_VOLUME);
                                break;
                        }
                    } else if(enc.direction() == -1){
                        angle += 18;
                        switch(vismate.get_screen()){
                            case SET_VOLUME :
                                for(int x = 240; x >= 0; x-=40){
                                    lcd.moveTo(SET_VOLUME, x-240, 0, angle);
                                    lcd.moveTo(SETTING_BACK, x, 0, angle);
                                }
                                voice.speak("Back to menu");
                                vismate.setScreen(SETTING_BACK);
                                break;
                            case SETTING_BACK :
                                for(int x = 240; x >= 0; x-=40){
                                    lcd.moveTo(SETTING_BACK, x-240, 0, angle);
                                    lcd.moveTo(REBOOT, x, 0, angle);
                                }
                                voice.speak("Restart device");
                                vismate.setScreen(REBOOT);
                                break;
                            case REBOOT :
                                for(int x = 240; x >= 0; x-=40){
                                    lcd.moveTo(REBOOT, x-240, 0, angle);
                                    lcd.moveTo(INFO_WIFI, x, 0, angle);
                                }
                                voice.speak("WiFi Information");
                                vismate.setScreen(INFO_WIFI);
                                break;
                            case INFO_WIFI :
                                for(int x = 240; x >= 0; x-=40){
                                    lcd.moveTo(INFO_WIFI, x-240, 0, angle);
                                    lcd.moveTo(SET_TIMEOUT, x, 0, angle);
                                }
                                lcd.load(screenTimeOut/6000, angle);
                                voice.speak("Timeout setting");
                                vismate.setScreen(SET_TIMEOUT);
                                break;
                            case SET_TIMEOUT :
                                for(int x = 240; x >= 0; x-=40){
                                    lcd.moveTo(SET_TIMEOUT, x-240, 0, angle);
                                    lcd.moveTo(SET_VOLUME, x, 0, angle);
                                }
                                lcd.load((vol_buff*10)/21, angle);
                                voice.speak("Set Volume");
                                vismate.setScreen(SET_VOLUME);
                                break;
                        }
                    }
                }
                blControl = millis();
                sleepCheck = millis();
            }

            if (enc.isClicked()){
                digitalWrite(TFT_BL, HIGH);
                debug(MAIN_TAG, "clicked");
                vol_buff = vismate.get_volume();
                switch(vismate.get_screen()){
                    case HOME_SCREEN :
                        vismate.talk(HOME_SCREEN);
                        break;
                    case NOTES :
                        for(int x = 240; x >= 0; x-=40){
                            lcd.moveTo(NOTES, 0, x-240, angle);
                            lcd.moveTo(LISTENING, 0, x, angle);
                        }
                        vismate.setScreen(LISTENING);
                        xiao.write(2);
                        voice.speak("Listening Started");
                        break;
                    case LISTENING :
                        for(int x = 0; x <= 240; x+=40){
                            lcd.moveTo(LISTENING, 0, x, angle);
                            lcd.moveTo(NOTES, 0, x-240, angle);
                        }
                        vismate.setScreen(NOTES);
                        xiao.write(0);
                        vismate.talk(NOTES);
                        break;
                    case SPEAK :
                        for(int x = 240; x >= 0; x-=40){
                            lcd.moveTo(SPEAK, 0, x-240, angle);
                            lcd.moveTo(SPEAK_SAVED_PHRASE, 0, x, angle);
                        }
                        vismate.setScreen(SPEAK_SAVED_PHRASE);
                        voice.speak("Text to Speech Started");
                        break;
                    case SPEAK_SAVED_PHRASE :
                        for(int x = 0; x <= 240; x+=40){
                            lcd.moveTo(SPEAK_SAVED_PHRASE, 0, x, angle);
                            lcd.moveTo(SPEAK, 0, x-240, angle);
                        }
                        vismate.setScreen(SPEAK);
                        vismate.talk(SPEAK);
                        break;
                    case NAVIGATION :
                        for(int x = 240; x >= 0; x-=40){
                            lcd.moveTo(NAVIGATION, 0, x-240, angle);
                            lcd.moveTo(OBJECT_DETECTION, 0, x, angle);
                        }
                        vismate.setScreen(OBJECT_DETECTION);
                        updateTof = true;
                        xiao.write(1);
                        debugVal(MAIN_TAG, "Update range status : ", updateTof ? "Active" : "Non-active");
                        voice.speak("Starting object detection");
                        break;
                    case OBJECT_DETECTION :
                        for(int x = 0; x <= 240; x+=40){
                            lcd.moveTo(OBJECT_DETECTION, 0, x, angle);
                            lcd.moveTo(NAVIGATION, 0, x-240, angle);
                        }
                        vismate.setScreen(NAVIGATION);
                        updateTof = false;
                        xiao.write(0);
                        debugVal(MAIN_TAG, "Update range status : ", updateTof ? "Active" : "Non-active");
                        vismate.talk(NAVIGATION);
                        break;
                    case MAPS :
                        for(int x = 240; x >= 0; x-=40){
                            lcd.moveTo(MAPS, 0, x-240, angle);
                            lcd.moveTo(UNIV_MAPS, 0, x, angle);
                        }
                        vismate.setScreen(UNIV_MAPS);
                        voice.speak("Here is maps to Brawijaya University");
                        break;
                    case UNIV_MAPS :
                        for(int x = 0; x <= 240; x+=40){
                            lcd.moveTo(UNIV_MAPS, 0, x, angle);
                            lcd.moveTo(MAPS, 0, x-240, angle);
                        }
                        vismate.setScreen(MAPS);
                        vismate.talk(MAPS);
                        break;
                    case SETTING :
                        for(int x = 240; x >= 0; x-=40){
                            lcd.moveTo(SETTING, 0, x-240, angle);
                            lcd.moveTo(SET_VOLUME, 0, x, angle);
                        }
                        lcd.load((vol_buff*10)/21, angle);
                        vismate.setScreen(SET_VOLUME);
                        voice.speak("Volume setting");
                        break;
                    case SET_VOLUME :
                        vol_buff+=7;
                        if(vol_buff>21) vol_buff = 0;
                        lcd.load((vol_buff*10)/21, angle);
                        vismate.set_volume(vol_buff);
                        voice.speak("Volume changed");
                        data.saveAt("Volume", String(vol_buff));
                        debugVal(MAIN_TAG,"Changed volume to ", vol_buff);
                        break;
                    case SET_TIMEOUT :
                        screenTimeOut+=15000;
                        if(screenTimeOut > 60000) screenTimeOut = 15000;
                        lcd.load(screenTimeOut/6000, angle);
                        data.saveAt("ScreenTimeOut", String(screenTimeOut));
                        voice.speak("Screen Time Out changed");
                        debugVal(MAIN_TAG,"Changed screen timeout to ", screenTimeOut);
                        break;
                    case INFO_WIFI :
                        for(int x = 240; x >= 0; x-=40){
                            lcd.moveTo(REBOOT, 0, x, angle);
                        }
                        vismate.setScreen(REBOOT);
                        voice.speak("Reboot");
                        break;
                    case REBOOT :
                        voice.speak("Restarting device");
                        vTaskDelay(1000 / portTICK_PERIOD_MS);
                        ESP.restart();
                        break;
                    case SETTING_BACK :
                        for(int x = 240; x >= 0; x-=40){
                            lcd.moveTo(SETTING, 0, x, angle);
                        }
                        vismate.setScreen(SETTING);
                        voice.speak("Setting");
                        break;
                }
                blControl = millis();
                sleepCheck = millis();
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void setup()
{
    Serial.begin(115200);
    xiao.begin(115200, SERIAL_8N1, 14, 21);
    xiao.onReceive(receiverCallback, true);

    delay(1000);
    rtc_gpio_hold_dis(GPIO_NUM_15);
    rtc_gpio_deinit(GPIO_NUM_16);

    vismate.init_lcd();

    print_wakeup_reason();
    // data.format();
    vismate.setup_control();
    vismate.init_connection();
    fb.begin(DEFAULT_URL, DEFAULT_KEY);
    
    rtc_gpio_deinit(GPIO_NUM_11);
    rtc_gpio_deinit(GPIO_NUM_12);
    rtc_gpio_deinit(GPIO_NUM_15);
    rtc_gpio_deinit(GPIO_NUM_17);
    rtc_gpio_deinit(GPIO_NUM_18);

    attachInterrupt(GPIO_NUM_16, sleep_isr, CHANGE);
    xTaskCreate(sleepTask, "ESP Sleep Mode Start", 5000, NULL, 3, NULL);
    battery.begin();
    lcd.show_device_logo();

    vismate.speaker_test();
    int saved_vol = data.read("Volume").toInt();
    vol_buff = saved_vol > 0 ? saved_vol : 21;
    debugVal(MAIN_TAG, "Saved volume : ", vol_buff);
    vismate.set_volume(vol_buff);

    int saved_timeout = data.read("ScreenTimeOut").toInt();
    screenTimeOut = saved_timeout > 0 ? saved_timeout : 30000;
    debugVal(MAIN_TAG, "Saved timeout : ", screenTimeOut);

    delay(1000);
    lcd.update_time(ntp.get_time(), ntp.get_date(), battery.get_percentage());
    
    tof.begin();
    enc.init(rotary_isr);

    xTaskCreate(connectionTask, "Check Connection", 10000, NULL, 3, NULL);
    xTaskCreate(controlTask, "Rotary Control Task", 15000, NULL, 4, NULL);

    sleepCheck = millis();
    blControl = millis();
}

int obj_range;

void loop(){
    if(!voice.isRunning() && sleepMode == false){
        if(updateTof && millis() - tofUpdate > 2000){
            int val = tof.get_centi();
            obj_range = val;
            debugVal(MAIN_TAG, "Distance (mm): ", val);
            tofUpdate = millis();
            debugVal(MAIN_TAG, "Send data...", fb.set(val, "Data/LNwCMmoksbSaT51dIjv83rvHp1j1/ToF"));

            if(obj_range > 2){
                xiao.write(1);
            } else{
                xiao.write(0);
            }
            blControl = millis();
        }

        if(millis() - sleepCheck > 300000){
            sleepMode = true;
        }

        if(vismate.get_screen() == LISTENING){
            String url_path = "Data/LNwCMmoksbSaT51dIjv83rvHp1j1/Hasil pengukuran/"+ntp.get_raw_date()+"/VR/"+String(ntp.epoch())+"/Rekaman1";
            if(_url_buff!=""){
                _url_buff = "\""+ _url_buff +"\"";
                if(fb.setString(_url_buff, url_path) == "ok"){
                    debug(MAIN_TAG, "Send Success");
                } else{
                    debug(MAIN_TAG, "Send failed");
                }
            }
        }

        if(new_obj && updateTof){
            if(fb.setString(_obj_buff, "Data/LNwCMmoksbSaT51dIjv83rvHp1j1/Detected Object") == "ok"){
                debug(MAIN_TAG, "Send Success");
                String voice_buff = _obj_buff + " detected on " + tof.get_range();
                voice.speak(voice_buff.c_str());
                new_obj = false;
            } else{
                debug(MAIN_TAG, "Send failed");
            }
            blControl = millis();
        }

        if(vismate.get_screen() == SPEAK_SAVED_PHRASE){
            String voice_buff = fb.getString("Data/LNwCMmoksbSaT51dIjv83rvHp1j1/TTS/");
            // if(voice_buff!=" "){
                voice.speak(voice_buff.c_str());
                // if(fb.setString(" ", "Data/LNwCMmoksbSaT51dIjv83rvHp1j1/TTS/") == "ok"){
                //     debug(MAIN_TAG, "Send Success");
                // } else{
                //     debug(MAIN_TAG, "Send failed");
                // }
            // }
            blControl = millis();
        }
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
}
