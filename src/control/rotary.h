#ifndef Rotary_h_
#define Rotary_h_

#include "Arduino.h"
#include "AiEsp32RotaryEncoder.h"

#define DEFAULT_A_PIN     19
#define DEFAULT_B_PIN     20
#define DEFAULT_BUT_PIN   48
#define DEFAULT_VCC_PIN   -1
#define DEFAULT_STEPS      4

class RotaryClass{
  private:
    AiEsp32RotaryEncoder encoder = AiEsp32RotaryEncoder(DEFAULT_A_PIN, DEFAULT_B_PIN, DEFAULT_BUT_PIN, DEFAULT_VCC_PIN, DEFAULT_STEPS);
    void (*ISR_Func)();

    int _rotary_position = 0;
    bool _click = false;
    bool _change = false;
    int _direction = 1; // -1 = counter cw, 1 = cw, 0 = error

  public:
    RotaryClass();
	  void IRAM_ATTR readEncoder();
    void init(void(*ISR_Func)(void));
    void read();
    bool isClicked();
    bool isChanged();
    int direction();
    int position();
    void setPosition(int pos);
};

extern RotaryClass enc;

#endif // Rotary_h_