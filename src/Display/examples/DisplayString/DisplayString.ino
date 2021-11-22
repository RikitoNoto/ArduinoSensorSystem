#include <RobotLCD.h>

#define cs   10
#define dc   9
#define rst  8

RobotLCD lcd = RobotLCD(cs, dc, rst);

void setup()
{
    lcd.begin();
    lcd.setBackgroundColor(Color::COLOR::BLACK);
}

void loop()
{
    lcd.display("Testing!", RobotLCD::TEXT_SIZE_MIDDLE);
}
