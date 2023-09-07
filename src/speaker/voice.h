#ifndef voice_h_
#define voice_h_

#include "Arduino.h"
#include "Audio.h"
#include "../device_config.h"

#define I2S_DOUT      42
#define I2S_BCLK      40
#define I2S_LRC       41

#define AUDIO_TAG "Audio"

class VoiceClass{
  public:
    void init(void);
    void change_volume(uint8_t volume);
    void speak(const char *buff);
  
  private:
    Audio audio;
};

extern VoiceClass voice;

#endif