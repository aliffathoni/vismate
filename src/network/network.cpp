#include "network.h"

DNSServer dnsServer;
AsyncWebServer server(80);

NetworkClass *net_instances;

NetworkClass::NetworkClass(){
  net_instances = this;
}

void NetworkClass::setupServer(){
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/html", index_html); 
      debug(TAG, "Client Connected");
  });
    
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
      String inputMessage;
      String inputParam;
  
      if (request->hasParam("ssid")) {
        inputMessage = request->getParam("ssid")->value();
        inputParam = "ssid";
        net_instances->ssid = inputMessage;
        data.saveAt("ssid", net_instances->ssid);
        debugVal(TAG, "SSID : ", net_instances->ssid);
      }

      if (request->hasParam("password")) {
        inputMessage = request->getParam("password")->value();
        inputParam = "password";
        net_instances->pass = inputMessage;
        data.saveAt("pass", net_instances->pass);
        debugVal(TAG, "Password : ", net_instances->pass);
      }
      request->send(200, "text/html", "The values entered by you have been successfully sent to the device <br><a href=\"/\">Return to Home Page</a>");
      debug(TAG, "SSID obtained!");
      net_instances->_connection_status = true;
      server.end();
  });
}

void NetworkClass::connect(String ssid, String pass){
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  debugVal(TAG, "Connecting to ", data.read("ssid"));
  WiFi.begin(ssid.c_str(), pass.c_str());
}

bool NetworkClass::get_status(){
  if(WiFi.status() == WL_CONNECTED){
    return true;
  } else{
    return false;
  }
}

void NetworkClass::begin(){
  unsigned long print = millis();
  if(data.read("ssid")==""){
    net_instances->reconnect(net_instances->ssid_ap);
    while(!net_instances->_connection_status){
      dnsServer.processNextRequest();
      if(millis() - print > 1000){
        Serial.print("-");
        print = millis();
      }
    }
    Serial.print("");
  } else{
    debug(TAG, "Data acquired");
    net_instances->ssid = data.read("ssid");
    net_instances->pass = data.read("pass");
  }

  net_instances->connect(net_instances->ssid, net_instances->pass);

  uint8_t connect_chance = 30;
  while (!net_instances->get_status()){
    if(millis() - print > 1000){
      Serial.print(".");
      print = millis();
      connect_chance--;
      if(connect_chance < 1){
        debug(TAG, "WiFi not found!");
        data.format();
        debug(TAG, "Restarting...");
        ESP.restart();
      }
    }
  }
  Serial.println("");
  debug(TAG, "Connected!");
}

void NetworkClass::reconnect(String ap_name){
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_name.c_str());
  debugVal(TAG, "AP IP address: ", WiFi.softAPIP());
  net_instances->setupServer();
  debug(TAG, "Starting DNS Server");
  dnsServer.start(53, "*", WiFi.softAPIP());
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
  //more handlers...
  server.begin();
}

String NetworkClass::get_ssid(){
    return net_instances->ssid;
}

String NetworkClass::get_ip(){
    return WiFi.localIP().toString();
}

NetworkClass net;