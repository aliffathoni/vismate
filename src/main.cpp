#include <Arduino.h>
#include "system/vismate.h"
#include "device_config.h"

int last_pos = 0;

void setup()
{
    Serial.begin(115200);
    
    size_t psram_size = esp_spiram_get_size();
    Serial.print("PSRAM Size ");
    Serial.println(psram_size);

    delay(1000);
    vismate.setup_control();
    vismate.lcd_test();
    vismate.speaker_test();
    delay(1000);
    vismate.screen(HOME_SCREEN);
}

void loop(){
    if(!digitalRead(3)){
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
            vismate.screen(SPEECH);
            break;
        case SPEECH:
            vismate.screen(NOTES);
            break;
        case NOTES:
            vismate.screen(HOME_SCREEN);
            break;
        default:
            vismate.screen(HOME_SCREEN);
            break;
      }

      vTaskDelay(200 / portTICK_PERIOD_MS);
    }

    if(!digitalRead(10)){
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
        case SPEECH:
            vismate.screen(NAVIGATION);
            break;
        case NOTES:
            vismate.screen(SPEECH);
            break;
        case HOME_SCREEN:
            vismate.screen(NOTES);
            break;
        default:
            vismate.screen(HOME_SCREEN);
            break;
      }

      vTaskDelay(200 / portTICK_PERIOD_MS);
    }

    if(!digitalRead(9)){
      vismate.screen(vismate.get_screen());
      
      vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}
