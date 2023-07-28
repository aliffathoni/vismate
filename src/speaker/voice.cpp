#include "voice.h"

VoiceClass *voice_instances;

void VoiceClass::init(){
  voice_instances = this;
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(21); //Volume min = 0, max = 21
}

void VoiceClass::speak(const char *buff){
  audio.connecttospeech(buff, "en");                      //Mengubah data digital suara ke analog
  neopixelWrite(RGB_BUILTIN,0,0,RGB_BRIGHTNESS); // Blue
  bool soundPlay = true;
  Serial.println(buff);

  while(soundPlay){
    audio.loop();
    if(!audio.isRunning()) {
      soundPlay = false;
      Serial.println("Audio Stopped");
      neopixelWrite(RGB_BUILTIN,0,0,0); // Blue
    }
  }
}

VoiceClass voice;