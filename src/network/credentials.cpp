#include "credentials.h"

CredentialsClass *memory;

CredentialsClass::CredentialsClass(){
  memory = this;
}

void CredentialsClass::saveAt(String dir_name, String value){
  dir.begin(memory->_directory, false);
  dir.putString(dir_name.c_str(), value.c_str());
  dir.end();
}

String CredentialsClass::read(String dir_name){
  dir.begin(memory->_directory, false);
  String res = dir.getString(dir_name.c_str(), "");
  return res;
}

void CredentialsClass::format(){
  dir.begin(memory->_directory, false);
  dir.clear();
  dir.end();
}

CredentialsClass data;