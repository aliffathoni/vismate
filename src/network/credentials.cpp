#include <Arduino.h>

#include "server.h"
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