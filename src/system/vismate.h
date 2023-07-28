#ifndef VISMATE_H_
#define VISMATE_H_

#include <Arduino.h>

class VisMateClass {
    public :
        VisMateClass();
        void speaker_test();
        void lcd_test();

    private :
        int _pin;
};

extern VisMateClass vismate;

#endif // VISMATE_H_