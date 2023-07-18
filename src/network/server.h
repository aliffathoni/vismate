#ifndef SERVER_H_
#define SERVER_H_

#include <Arduino.h>

// credentials
void load(void);
void reset(void);
void write(String ssid, String password);

// ip
boolean isIp(String str);
String toStringIp(IPAddress ip);

// webhandle
void reset_credentials(void);
void load_credentials(void);
void write_credentials(void);

#endif // SERVER_H_
