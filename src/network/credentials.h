#ifndef CREDENDTIALS_H_
#define CREDENDTIALS_H_

#include <Arduino.h>

#include "network.h"
#include <Preferences.h>

Preferences pf;

void load(){
    pf.begin("credentials", false);

    pf.getString("ssid", "");
    pf.getString("password", "");

    pf.end();
}

void reset(){
    pf.begin("credentials", false);
    pf.clear();
    pf.end();
}

void write(String ssid, String password){
    pf.begin("credentials", false);

    pf.putString("ssid", ssid);
    pf.putString("password", password);

    pf.end();
}

#endif // CREDENDTIALS_H_