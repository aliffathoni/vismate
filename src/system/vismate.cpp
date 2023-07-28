#include "vismate.h"
#include "../device_config.h"
#include "../network/server.h"
#include "../display/lcd.h"
#include "../speaker/voice.h"

VisMateClass *vismate_instances;

VisMateClass::VisMateClass(){
    vismate_instances = this;
    _pin = DEFAULT_EMG_PIN;
}

void VisMateClass::lcd_test(){
    lcd.init_tft();
    lcd.boot();
}

void VisMateClass::speaker_test(){
    voice.init();
    WiFi.begin("Kara VIP", "icecoffeeshaken");
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(250);
    }
    Serial.println(".");
    Serial.print("Connected at ");
    Serial.println(WiFi.localIP());

    voice.speak("Device Connected");
}

VisMateClass vismate;