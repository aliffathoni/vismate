#include "vismate.h"

VisMateClass *vismate_instances;

VisMateClass::VisMateClass(){
    vismate_instances = this;
}

void VisMateClass::setup_control(){
    pinMode(_up_pin, INPUT_PULLUP);
    pinMode(_mid_pin, INPUT_PULLUP);
    pinMode(_down_pin, INPUT_PULLUP);
}

void VisMateClass::setup_control(uint8_t up_pin, uint8_t mid_pin, uint8_t down_pin){
    _up_pin = up_pin;
    _mid_pin = mid_pin;
    _down_pin = down_pin;
    
    pinMode(_up_pin, INPUT_PULLUP);
    pinMode(_mid_pin, INPUT_PULLUP);
    pinMode(_down_pin, INPUT_PULLUP);
}

void VisMateClass::lcd_test(){
    lcd.init_tft();
    lcd.boot();
}

void VisMateClass::speaker_test(){
    voice.init();
    
    WiFi.begin("R3", "01062003");
    while(WiFi.status() != WL_CONNECTED){
        Serial.println(".");
        delay(100);
    }

    Serial.println(".");
    Serial.print("Connected at ");
    Serial.println(WiFi.localIP());

    voice.speak("Device Connected");
}

void VisMateClass::init_i2c(){
    Wire.begin(12, 11);
}

void VisMateClass::scan_i2c(){
    byte error, address;
    int nDevices = 0;

    delay(5000);

    Serial.println("Scanning for I2C devices ...");
    for(address = 0x01; address < 0x7f; address++){
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0){
        Serial.printf("I2C device found at address 0x%02X\n", address);
        nDevices++;
        } else if(error != 2){
        Serial.printf("Error %d at address 0x%02X\n", error, address);
        }
    }
    if (nDevices == 0){
        Serial.println("No I2C devices found");
    }
}

void VisMateClass::screen(Menu_screen_t new_screen){
    _last_screen = _screen_now;
    _screen_now = new_screen;

    if(_last_screen == SETTING && _screen_now == HOME_SCREEN){
        for(int x = 240; x >= 0; x-=40){
            lcd.menu(_last_screen, x-240);
            lcd.menu(_screen_now, x);
        }
    }   else if(_last_screen == HOME_SCREEN && _screen_now == SETTING){
        for(int x = 0; x <= 240; x+=40){
          lcd.menu(_last_screen, x);
          lcd.menu(_screen_now, x-240);
        }
    }   else if(_last_screen < _screen_now){
        for(int x = 240; x >= 0; x-=40){
            lcd.menu(_last_screen, x-240);
            lcd.menu(_screen_now, x);
        }
    }   else if(_last_screen > _screen_now){
        for(int x = 0; x <= 240; x+=40){
            lcd.menu(_last_screen, x);
            lcd.menu(_screen_now, x-240);
        }
    }   else{
        lcd.menu(_screen_now, 0);
    }

    switch (new_screen) {
        case HOME_SCREEN:
            voice.speak("Home screen");
            break;
        case NOTES:
            voice.speak("Notes");
            break;
        case SPEECH:
            voice.speak("Speech to text");
            break;
        case NAVIGATION:
            voice.speak("Navigation");
            break;
        case MAPS:
            voice.speak("Maps");
            break;
        case SETTING:
            voice.speak("Setting");
            break;
        default:
            voice.speak("Default");
            break;
    }
}

Menu_screen_t VisMateClass::get_screen(){
    return _screen_now;
}

VisMateClass vismate;