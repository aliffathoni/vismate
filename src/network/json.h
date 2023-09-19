#ifndef Json_h_
#define Json_h_

#include <Arduino.h>
#include "ArduinoJson.h"

class JsonClass{
  private:
    String _buffer;

  public:
    JsonClass();
    String read(String component);
    void send(String component, int value);
};

extern JsonClass json;

#endif // Json_h_