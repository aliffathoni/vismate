#include "range.h"

ToFClass *tof_instances;

ToFClass::ToFClass(){
    tof_instances = this;
}

void ToFClass::begin(){

}

int ToFClass::get_meter(){
    int sensor_data = 0;

    return sensor_data / 1000;
}

int ToFClass::get_centi(){
    int sensor_data = 0;

    return sensor_data / 10;
}

int ToFClass::get_mili(){
    int sensor_data = 0;

    return sensor_data;
}

ToFClass tof;