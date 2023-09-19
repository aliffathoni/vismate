#include "json.h"

JsonClass *json_instances;

JsonClass::JsonClass(){
  json_instances = this;
}

String JsonClass::read(String component){
  String _buffer;
  DynamicJsonDocument  doc(200);
  DeserializationError error = deserializeJson(doc, _buffer);

  // Test if parsing succeeds.
  if (error) {
    return error.f_str();
  }
  
  const char* obj = doc["object"];
  String _obj_buff = obj;
  
  return _obj_buff;
}

void JsonClass::send(String component, int value){

 
}