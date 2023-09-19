#include "rotary.h"

RotaryClass *rotary_instances;

RotaryClass::RotaryClass(){
  rotary_instances = this;
}

void IRAM_ATTR RotaryClass::readEncoder(){
  encoder.readEncoder_ISR();
}

void RotaryClass::init(void(*ISR_Func)(void)){
  encoder.begin();
  encoder.setup(ISR_Func);
  encoder.setBoundaries(-10, 10, false);
  encoder.disableAcceleration();
  encoder.setEncoderValue(0);
}

void RotaryClass::read(){
  if(encoder.encoderChanged()){
    int buff = encoder.readEncoder();
    
    if(buff > _rotary_position) _direction = 1;
    else if(buff < _rotary_position) _direction = -1;
    else _direction = 0;
    _rotary_position = buff;

    _change = true;
  } else{
    _change = false;
  }

  if(encoder.isEncoderButtonClicked()){
    _click = true;
  } else{
    _click = false;
  }
}

bool RotaryClass::isClicked(){
  return _click;
}

bool RotaryClass::isChanged(){
  return _change;
}

int RotaryClass::direction(){
  return _direction;
}

int RotaryClass::position(){
  return _rotary_position;
}

void RotaryClass::setPosition(int pos){
  _rotary_position = pos;
}

RotaryClass enc;
