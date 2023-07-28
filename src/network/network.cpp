#include "network.h"

NetworkClass *network_instances;

NetworkClass::NetworkClass(void){
    network_instances = this;
}

bool NetworkClass::begin(){
    // WiFi.disconnect();
    WiFi.begin(_net_ssid, _net_pass);
    uint8_t connect_chances = 32;
    while(WiFi.status() != WL_CONNECTED){
        connect_chances--;
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }

    if(connect_chances >= 0){
        return true;
    } else{
        return false;
    }
}

NetworkClass net;