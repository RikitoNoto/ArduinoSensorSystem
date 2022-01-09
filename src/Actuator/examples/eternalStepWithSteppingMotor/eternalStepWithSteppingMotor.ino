#include <SteppingMotor.h>

SteppingMotor stepping_motor(8, 9, 10, 11);

void setup()
{

}

void loop()
{
    stepping_motor.reversStep();
    delay(50);
}
