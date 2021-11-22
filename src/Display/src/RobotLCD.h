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
        virtual void display(char* str, BYTE size);
            static const BYTE TEXT_SIZE_MAXIMUM;
            static const BYTE TEXT_SIZE_LARGE;
            static const BYTE TEXT_SIZE_MIDDLE;
            static const BYTE TEXT_SIZE_SMALL;
            static const BYTE TEXT_SIZE_MINIMUM;

        virtual void setBackgroundColor(Color::COLOR color);

    private:
        TFT* mp_tft;
};

#endif // _ROBOT_LCD_H_
