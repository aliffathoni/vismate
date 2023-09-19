#ifndef Firebase_h_
#define Firebase_h_

#include <Arduino.h>
#include <FirebaseESP32.h>
#define FIREBASE_USE_PSRAM

class FirebaseClass {
  private:
    FirebaseData fbdo;
    FirebaseAuth auth;
    FirebaseConfig config;

  public:
    FirebaseClass();
    void begin(String url, String secret);
    String set(int data, String path);
    String setString(String data, String path);
    int get(String path);
    String getString(String path);
};

extern FirebaseClass fb;

#endif // Firebase_h_