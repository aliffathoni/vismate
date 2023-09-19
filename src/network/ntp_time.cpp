#include "ntp_time.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 28800);

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

  String month_name[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  String date_value = date_format +" "+ month_name[timeClient.getMonth() - 1];
  return date_value;
}

String NTPClass::get_raw_date(){
  timeClient.update();
  String date_value = timeClient.getFormattedDate();
  return date_value;
}

long NTPClass::epoch(){
  timeClient.update();
  return timeClient.getEpochTime();
}

NTPClass ntp;