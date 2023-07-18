#include <Arduino.h>

#include "vismate.h"
#include "../device_config.h"
#include "../network/server.h"
#include "../camera/object_detection.h"

visMate::visMate(){
    _pin = DEFAULT_EMG_PIN;
}

visMate::visMate(uint8_t pin){
    _pin = pin;
}

void visMate::init_camera(){
    initCamera();
    reset_credentials();
}

String visMate::get_object(){
    write_credentials();
    load_credentials();
    return getObject();
}