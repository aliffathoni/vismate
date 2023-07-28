#include <Arduino.h>

#include "credentials.h"
#include "ip_handle.h"
#include "web_handle.h"

void reset_credentials(){
    reset();
}

void load_credentials(){
    load();
}

void write_credentials(){
    write("example", "example");
}