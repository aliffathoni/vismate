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
    String get_ssid();
    String get_ip();
    void set_credentials(const char *ssid, const char *pass);
    bool get_net_status();
    void begin();
};

extern NetworkClass net;

#endif // NETWORK_H_