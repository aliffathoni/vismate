#ifndef NETWORK_H_
#define NETWORK_H_

#include <Arduino.h>
#include <WiFi.h>

class NetworkClass {
  private:
    const char *_net_ssid = "3DPractical";
    const char *_net_pass = "embeddedelectronics";

  public:
    NetworkClass(void);
    bool begin();
};

extern NetworkClass net;

#endif // NETWORK_H_