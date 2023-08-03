#ifndef DEVICE_CONFIG_H_
#define DEVICE_CONFIG_H_

#define DEFAULT_UP_PIN      3
#define DEFAULT_MID_PIN     9
#define DEFAULT_DOWN_PIN    10

#define FIREBASE_USE_PSRAM

#define DEFAULT_SSID        "R3"
#define DEFAULT_PASS        "01062003"
#define DEFAULT_AP_SSID     "vismate"

#define DEFAULT_DEVICE_NAME "device-"+String((uint32_t)ESP.getEfuseMac(), HEX)

#define debug(x, y)         Serial.print("[");Serial.print(millis());Serial.print("] "); Serial.print("[");Serial.print(x);Serial.print("] "); Serial.println(y);
#define debugVal(x, y, z)   Serial.print("[");Serial.print(millis());Serial.print("] "); Serial.print("[");Serial.print(x);Serial.print("] "); Serial.print(y); Serial.println(z);

typedef enum {
    // Main Menu
    HOME_SCREEN,
    NOTES,
    SPEAK,
    NAVIGATION,
    MAPS,
    SETTING,

    // Extra
    LOADING,

    // Notes
    LISTENING,
    SPEECH_TO_TEXT,
    LISTENING_RESULT,

    // Speak
    SPEAK_SAVED_PHRASE,
    SPEAK_GET_APP,
    SPEAK_PLAY_RESULT,

    // Navigation
    LOADING_OBJECT,
    OBJECT_DETECTION,

    // Maps
    HOME_MAPS,
    UNIV_MAPS,
    SHOW_MAPS,

    // Setting
    ROTATION,
    SET_ROTATE,
    REBOOT,
    REBOOT_CONFIRM,
    CONNECTIVITY,
    SHOW_NETWORK
} Menu_screen_t;

#endif // DEVICE_CONFIG_H_