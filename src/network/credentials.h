#ifndef CREDENDTIALS_H_
#define CREDENDTIALS_H_

#include <Arduino.h>
#include <Preferences.h>

class CredentialsClass{
  private:
    Preferences dir;
    const char *_directory = "config";
  public:
    CredentialsClass();
    void saveAt(String dir_name, String value);
    String read(String dir_name);
    void format();
};

extern CredentialsClass data;

#endif // CREDENDTIALS_H_