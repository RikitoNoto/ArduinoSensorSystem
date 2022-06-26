#ifndef _COLOR_H_
#define _COLOR_H_

#include <DataType.h>

class Color
{
public:
    enum COLOR
    {
        NONE = 0,
        WHITE,
        BLACK,
        RED,
        BLUE,
        GREEN,
        DEFINE_MAX
    };

    struct ColorRGB
    {
        BYTE m_r;
        BYTE m_g;
        BYTE m_b;
    };

    static const ColorRGB COLOR_RGB[];


    static const ColorRGB returnColorRGB(COLOR color);
    static ColorRGB* setRGB(COLOR color, ColorRGB* color_struct);
    BOOL isSameColorRGB(const ColorRGB* color1, const ColorRGB* color2);

private:

    static ColorRGB* setColorRGB(BYTE r, BYTE g, BYTE b, ColorRGB* color_struct);
};

#endif // _COLOR_H_