#ifndef DEVICE_CONFIG_H_
#define DEVICE_CONFIG_H_

#include <Arduino.h>
#include <String.h>
#include "display/lcd.h"

#define DEFAULT_BUTTON_PIN      16

#define FIREBASE_USE_PSRAM

#define DEFAULT_SSID        "R3"
#define DEFAULT_PASS        "01062003"
#define DEFAULT_AP_SSID     "vismate"

#define DEFAULT_URL         "vismate-fef88-default-rtdb.firebaseio.com"
#define DEFAULT_KEY         "lvXzLsvRfQdOoK4BHCfYg9VETtzKjevxkqnLNGdU"

#define DEFAULT_DEVICE_CODE (uint32_t)ESP.getEfuseMac()

#define debug(x, y)         Serial.print("[");Serial.print(millis());Serial.print("]"); Serial.print("[");Serial.print(x);Serial.print("] "); Serial.println(y);
#define debugVal(x, y, z)   Serial.print("[");Serial.print(millis());Serial.print("]"); Serial.print("[");Serial.print(x);Serial.print("] "); Serial.print(y); Serial.println(z);

#endif // DEVICE_CONFIG_H_