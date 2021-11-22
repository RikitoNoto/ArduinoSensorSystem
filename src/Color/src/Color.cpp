#include <Color.h>

const Color::ColorRGB Color::COLOR_RGB[]   ={
    // NONE:
    {  0,  0,  0},
    // WHITE:
    {255,255,255},
    // BLACK:
    {  0,  0,  0},
    // RED:
    {255,  0,  0},
    // BLUE:
    {  0,  0,255},
    // GREEN:
    {  0,255,  0},

};

const Color::ColorRGB Color::returnColorRGB(Color::COLOR color)
{
    if(Color::COLOR::DEFINE_MAX <= color)
    {
        color = COLOR::NONE;
    }

    return Color::COLOR_RGB[color];
}

Color::ColorRGB* Color::setRGB(Color::COLOR color, ColorRGB* color_struct)
{
    switch(color)
    {
        case Color::COLOR::WHITE:
            setColorRGB(255, 255, 255, color_struct);
        case Color::COLOR::BLACK:
            setColorRGB(0, 0, 0, color_struct);
        default:
            ;
    }

    return color_struct;
}

Color::ColorRGB* Color::setColorRGB(BYTE r, BYTE g, BYTE b, ColorRGB* color_struct)
{
    if(nullptr != color_struct)
    {
        color_struct->m_r = r;
        color_struct->m_g = g;
        color_struct->m_b = b;
    }
    
    return color_struct;
}