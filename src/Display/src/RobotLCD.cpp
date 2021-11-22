#include <RobotLCD.h>
#include <Color.h>

#include <TFT.h>


const BYTE RobotLCD::TEXT_SIZE_MAXIMUM  = 5;
const BYTE RobotLCD::TEXT_SIZE_LARGE    = 4;
const BYTE RobotLCD::TEXT_SIZE_MIDDLE   = 3;
const BYTE RobotLCD::TEXT_SIZE_SMALL    = 2;
const BYTE RobotLCD::TEXT_SIZE_MINIMUM  = 1;

RobotLCD::RobotLCD(BYTE cs, BYTE dc, BYTE reset)
{
    this->mp_tft = new TFT(cs, dc, reset);
}

RobotLCD::~RobotLCD()
{
    delete this->mp_tft;
}

void RobotLCD::begin()
{
    this->mp_tft->begin();
}

void RobotLCD::display(char* str, BYTE size)
{
    this->mp_tft->setTextSize(static_cast<uint8_t>(size));
    this->mp_tft->text(str, 0, 0);
}

void RobotLCD::setBackgroundColor(Color::COLOR color)
{
    const Color::ColorRGB rgb = Color::returnColorRGB(color);
    this->mp_tft->background(static_cast<uint8_t>(rgb.m_r), static_cast<uint8_t>(rgb.m_g), static_cast<uint8_t>(rgb.m_b));
}
