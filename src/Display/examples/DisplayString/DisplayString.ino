#include <RobotLCD.h>

#define cs   10
#define dc   9
#define rst  8

RobotLCD lcd = RobotLCD(cs, dc, rst);


void setup()
{
    Serial.begin(9600);
    lcd.begin();
    lcd.setBackgroundColor(Color::COLOR::BLACK);
}

void loop()
{
    lcd.display("Testing!", new Point<DWORD>(10,10), Display_if::TEXT_SIZE_SMALL);   
}
