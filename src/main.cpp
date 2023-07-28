#include <Arduino.h>
#include "system/vismate.h"

void setup()
{
    Serial.begin(115200);
    
    size_t psram_size = esp_spiram_get_size();
    Serial.print("PSRAM Size ");
    Serial.println(psram_size);

    delay(1000);

    vismate.speaker_test();
    vismate.lcd_test();
}

void loop()
{}
