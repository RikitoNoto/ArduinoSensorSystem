#include <RobotLCD.h>
#include <Color.h>

#include <TFT.h>

/**
* @brief constructor.
* @param[in] cs pin no of cs for spi communication.
* @param[in] dc pin no of dc for spi communication.
* @param[in] reset pin no of reset for spi communication.
*/
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

/**
* @brief display text.
* @param[in] str the text for display.
* @param[in] pos position of to display text.
* @param[in] size size of the text.
*/
void RobotLCD::display(char* str, Point<DWORD>* pos, BYTE size)
{
    this->display(str, pos, size, Color::COLOR::WHITE);
}

/**
* @brief display text.
* @param[in] str the text for display.
* @param[in] pos position of to display text.
* @param[in] size size of the text.
* @param[in] color color of the text.
*/
void RobotLCD::display(char* str, Point<DWORD>* pos, BYTE size, Color::COLOR color)
{
    DWORD x = 0;
    DWORD y = 0;
    if(nullptr != pos)
    {
        x = pos->getX();
        y = pos->getY();
    }

    // set the color of text.
    const Color::ColorRGB rgb = Color::returnColorRGB(color);
    this->mp_tft->stroke(static_cast<uint8_t>(rgb.m_r), static_cast<uint8_t>(rgb.m_g), static_cast<uint8_t>(rgb.m_b));

    // set the size of text.
    this->mp_tft->setTextSize(static_cast<uint8_t>(size));

    // display text.
    this->mp_tft->text(str, static_cast<int16_t>(x), static_cast<int16_t>(y));
}

/**
* @brief set background color.
* @param[in] color color of to set.
*/
void RobotLCD::setBackgroundColor(Color::COLOR color)
{
    const Color::ColorRGB rgb = Color::returnColorRGB(color);
    this->mp_tft->background(static_cast<uint8_t>(rgb.m_r), static_cast<uint8_t>(rgb.m_g), static_cast<uint8_t>(rgb.m_b));
}