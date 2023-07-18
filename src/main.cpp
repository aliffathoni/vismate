#include <Arduino.h>
#include "system/vismate.h"

visMate vis;

void setup()
{
    Serial.begin(115200);
    
    size_t psram_size = esp_spiram_get_size();
    Serial.print("PSRAM Size ");
    Serial.println(psram_size);

    vis.init_camera();
}

void loop()
{
    vis.get_object();
}
