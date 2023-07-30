#ifndef DEVICE_CONFIG_H_
#define DEVICE_CONFIG_H_

#define DEFAULT_UP_PIN 3
#define DEFAULT_MID_PIN 9
#define DEFAULT_DOWN_PIN 10

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
    OBJECT_DETECTION,

    // Maps
    HOME_MAPS,
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