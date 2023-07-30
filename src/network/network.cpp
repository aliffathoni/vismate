#include "network.h"

NetworkClass *network_instances;

NetworkClass::NetworkClass(void){
    network_instances = this;
}

bool NetworkClass::get_net_status(){
    if(WiFi.status() != WL_CONNECTED){
        return false;
    }

    return true;
}

String NetworkClass::get_ip(){
    return String(WiFi.localIP());
}

String NetworkClass::get_ssid(){
    return _net_ssid;
}

void NetworkClass::set_credentials(const char *ssid, const char *pass){
    _net_ssid = ssid;
    _net_pass = pass;
}

void NetworkClass::begin(){
    WiFi.disconnect();
    WiFi.begin(_net_ssid, _net_pass);
}

NetworkClass net;