#include <Arduino.h>

#include "vismate.h"

visMate::visMate(){
}

visMate::visMate(uint8_t pin){
    _pin = pin;
}

void visMate::init_camera(){
    initCamera();
}

String visMate::get_object(){
    return getObject();
}