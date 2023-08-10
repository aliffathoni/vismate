#include "ntp_time.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200);

NTPClass *time_instances;

NTPClass::NTPClass(){
  time_instances = this;
}

void NTPClass::begin(){
  timeClient.begin();
}

String NTPClass::get_time(){
  timeClient.update();
  return timeClient.getFormattedTime().substring(0, 5);
}

String NTPClass::get_date(){
  timeClient.update();
  String date_format = String(timeClient.getDate());
  String date_value = timeClient.getFormattedDate().substring(0,3) +" "+ date_format;
  return date_value;
}

String NTPClass::get_raw_date(){
  timeClient.update();
  String date_value = timeClient.getFormattedDate();
  return date_value;
}

NTPClass ntp;