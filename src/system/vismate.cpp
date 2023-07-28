#include "vismate.h"

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
    
    WiFi.begin("3DPractical", "embeddedelectronics");
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

VisMateClass vismate;