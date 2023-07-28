#ifndef voice_h_
#define voice_h_

#include "Arduino.h"
#include "Audio.h"

#define I2S_DOUT      4
#define I2S_BCLK      5
#define I2S_LRC       6

class VoiceClass{
  public:
    void init(void);
    void speak(const char *buff);
  
  private:
    Audio audio;
};

extern VoiceClass voice;

#endif