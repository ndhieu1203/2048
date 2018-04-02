#ifndef _COLORDISPLAY_H_INCLUDED
#define _COLORDISPLAY_H_INCLUDED

#include <windows.h>

struct ColorCharacter {
    unsigned char color;
    unsigned char character;
} ;

class ColorDisplay {
    public:
        ColorDisplay();
        void setColorCharacterAtPosition( ColorCharacter cc , COORD pos);
        void setColorCharacterAtPosition( ColorCharacter cc , short xPos , short yPos );
    private:
        HANDLE outConsole;
};
#endif // COLORDISPLAY_H_INCLUDED
