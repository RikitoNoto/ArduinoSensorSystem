
#include <RobotLCD.h>

#define cs   10
#define dc   9
#define rst  8

RobotLCD lcd = RobotLCD(cs, dc, rst);
Color::COLOR color1 = Color::COLOR::RED;
Color::COLOR color2 = Color::COLOR::BLUE;

void setup()
{
    lcd.begin();
    lcd.setBackgroundColor(color1);
}

void loop()
{
    delay(1000);
    lcd.setBackgroundColor(color2);
    delay(1000);
    lcd.setBackgroundColor(color1);
}
