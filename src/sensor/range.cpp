#include "range.h"

ToFClass *tof_instances;

ToFClass::ToFClass(){
    tof_instances = this;
}

void ToFClass::begin(){
    lox.begin();
    // lox.configSensor(lox.VL53L0X_SENSE_LONG_RANGE);
}

String ToFClass::get_range(){
    int sensor_data = get_mili();

    if(sensor_data > 1000){
        String result = String(sensor_data / 1000) + " meters";
        return result;
    } else if(sensor_data > 10){
        String result = String(sensor_data / 10) + " centimeters";
        return result;
    } else{
        String result = String(sensor_data) + " centimeters";
        return result;
    }
}

int ToFClass::get_meter(){
    int sensor_data = 0;
    VL53L0X_RangingMeasurementData_t measure;
    
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
    sensor_data = measure.RangeStatus != 4 ? measure.RangeMilliMeter / 1000 : 0;

    return sensor_data;
}

int ToFClass::get_centi(){
    int sensor_data = 0;
    VL53L0X_RangingMeasurementData_t measure;
    
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
    sensor_data = measure.RangeStatus != 4 ? measure.RangeMilliMeter / 10 : 0;

    return sensor_data;
}

int ToFClass::get_mili(){
    int sensor_data = 0;
    VL53L0X_RangingMeasurementData_t measure;
    
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
    sensor_data = measure.RangeStatus != 4 ? measure.RangeMilliMeter : 0;

    return sensor_data;
}

ToFClass tof;