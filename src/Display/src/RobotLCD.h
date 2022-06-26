#ifndef _ROBOT_LCD_H_
#define _ROBOT_LCD_H_


#include <DataType.h>
#include <Color.h>
#include <Display_if.h>

class TFT;

class RobotLCD : public Display_if
{
    public:
        RobotLCD(BYTE cs, BYTE dc, BYTE reset);
        virtual ~RobotLCD();
        virtual void begin();
        virtual void display(const char* str, Point<DWORD>* pos, BYTE size);
        virtual void display(const char* str, Point<DWORD>* pos, BYTE size, Color::COLOR color);

        virtual void setBackgroundColor(Color::COLOR color);

    private:
        TFT* mp_tft;
};

#endif // _ROBOT_LCD_H_
