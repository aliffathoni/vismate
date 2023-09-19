#include "voice.h"

VoiceClass *voice_instances;

VoiceClass::VoiceClass(){
  voice_instances = this;
}

void VoiceClass::init(){
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(21); //Volume min = 0, max = 21
}

void VoiceClass::change_volume(uint8_t volume){
  audio.setVolume(volume);
}

void VoiceClass::speak(const char *buff){
  audio.connecttospeech(buff, "en");                      //Mengubah data digital suara ke analog
  bool soundPlay = true;
  debugVal(AUDIO_TAG,"Audio out : ",buff);

  while(soundPlay){
    audio.loop();
    if(!audio.isRunning()) {
      soundPlay = false;
      debug(AUDIO_TAG, "Audio Stopped");
    }
  }
}

void VoiceClass::salam(){
  audio.connecttospeech("السَّلَامُ عَلَيْكُمْ وَرَحْمَةُ اللهِ وَبَرَكَاتُهُ", "ar");
  // audio.connecttospeech("こんにちは！フィルミトンですどうも！", "ja");
  bool soundPlay = true;
  debug(AUDIO_TAG,"Audio out");

  while(soundPlay){
    audio.loop();
    if(!audio.isRunning()) {
      soundPlay = false;
      debug(AUDIO_TAG, "Audio Stopped");
    }
  }
}

bool VoiceClass::isRunning(){
  return audio.isRunning();
}

VoiceClass voice;