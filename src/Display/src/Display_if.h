#ifndef _DISPLAY_IF_H_
#define _DISPLAY_IF_H_

#include <Color.h>

class Display_if
{
    public:
        virtual void begin() = 0;
        virtual void display(char* str, BYTE size) = 0;
        virtual void setBackgroundColor(Color::COLOR color) = 0;
};

#endif // _DISPLAY_IF_H_