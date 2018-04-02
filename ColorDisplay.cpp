#include "ColorDisplay.h"

ColorDisplay::ColorDisplay()
{
    outConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}
void ColorDisplay::setColorCharacterAtPosition( ColorCharacter cc , COORD pos)
{
    DWORD garbage = 0;
    FillConsoleOutputCharacter(outConsole, (TCHAR) cc.character, 1, pos, &garbage);
    FillConsoleOutputAttribute(outConsole, cc.color, 1, pos, &garbage);
}
void ColorDisplay::setColorCharacterAtPosition( ColorCharacter cc , short xPos , short yPos )
{
    COORD pos = { xPos , yPos };
    setColorCharacterAtPosition(cc, pos);
}
