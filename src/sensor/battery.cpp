#include "battery.h"

BatteryClass *batt_instances;

BatteryClass::BatteryClass(){
  batt_instances = this;
}

void BatteryClass::begin(){
  pinMode(_pin, INPUT);
}

uint8_t BatteryClass::get_percentage(){
  int batt_buff = analogReadMilliVolts(_pin);
  if(batt_buff < 2800){
    return 0;
  } else if(batt_buff > 3200){
    return 100;
  } else{
    return map(batt_buff, 2800, 3200, 0, 100);
  }
}

float BatteryClass::get_voltage(){
  return analogReadMilliVolts(_pin)/1000.0;
}

BatteryClass battery;