#include <Arduino.h>

#include "server.h"

void reset_credentials(){
    reset();
}

void load_credentials(){
    load();
}

void write_credentials(){
    write("example", "example");
}