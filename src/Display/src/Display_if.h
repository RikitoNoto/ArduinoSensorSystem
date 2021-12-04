#ifndef _DISPLAY_IF_H_
#define _DISPLAY_IF_H_

#include <Color.h>
#include <Point.h>

class Display_if
{
    public:
        virtual void begin() = 0;
        virtual void display(char* str, Point<DWORD>* pos, BYTE size) = 0;
        virtual void display(char* str, Point<DWORD>* pos, BYTE size, Color::COLOR color) = 0;
            enum DISPLAY_SIZE : BYTE
            {
                TEXT_SIZE_MINIMUM = 1,
                TEXT_SIZE_SMALL,
                TEXT_SIZE_MIDDLE,
                TEXT_SIZE_LARGE,
                TEXT_SIZE_MAXIMUM
            };
        virtual void setBackgroundColor(Color::COLOR color) = 0;
};

#endif // _DISPLAY_IF_H_