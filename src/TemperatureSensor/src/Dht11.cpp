#include <Arduino.h>
#include "Dht11.h"

Dht11::Dht11(BYTE datapin_no)
{

}

void Dht11::start()
{
    pinMode(8, INPUT);
    digitalWrite(8, LOW);
}