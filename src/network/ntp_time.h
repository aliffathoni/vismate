#ifndef NTP_TIME_H_
#define NTP_TIME_H_

#include <Arduino.h>
#include "network.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

class NTPClass {
  public:
    NTPClass();
    void begin();
    String get_time();
    String get_date();
    String get_raw_date();
};

extern NTPClass ntp;

#endif // NTP_TIME_H_