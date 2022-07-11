#include <Arduino.h>
#include <string.h>
#include "DataType.h"

#define DEFAULT_PIN_COUNT               (14)

BYTE getPinCount(ARDUINO_TYPE type);

Serial_ Serial;

static ARDUINO_TYPE target_arduino_type;      // current test arduino type

static uint8_t* pin_set_modes;      // pin modes
static uint8_t* pin_output_values;  // digital write values
static uint8_t* pin_input_values;   // digital read values

static bool* is_write_high;
static bool* is_write_low;

unsigned long micros()
{
    return 0;
}

void pinMode(uint8_t pin, uint8_t mode)
{
    pin_set_modes[pin] = mode;
}

void digitalWrite(uint8_t pin, uint8_t val)
{
    if(pin_set_modes[pin] == OUTPUT){
        pin_output_values[pin] = val;

        if(val == HIGH)
        {
            is_write_high[pin] = true;
        }
        else if(val == LOW)
        {
            is_write_low[pin] = true;
        }
    }
}

int digitalRead(uint8_t pin)
{
    return pin_input_values[pin];
}

/**
 * @brief   returns whether the pin mode is correct.
 */
bool isPinMode(uint8_t pin, uint8_t mode)
{
    return pin_set_modes[pin] == mode;
}

/**
 * @brief   returns whether the pin output is correct.
 */
bool isPinOutput(uint8_t pin, uint8_t val)
{
    return pin_output_values[pin]==val;
}

void clearWriteInfo(void)
{
    memset(is_write_high, false, getPinCount(target_arduino_type));
    memset(is_write_low, false, getPinCount(target_arduino_type));
}

/**
 * @brief   returns whether the pin output has been high even once.
 */
bool isWriteHigh(uint8_t pin)
{
    return is_write_high[pin];
}

/**
 * @brief   returns whether the pin output has been low even once.
 */
bool isWriteLow(uint8_t pin)
{
    return is_write_low[pin];
}

void setReadValue(uint8_t pin, int value)
{
    pin_input_values[pin] = value;
}

void setupSpyArduino(ARDUINO_TYPE type)
{
    target_arduino_type = type;

    pin_set_modes = new uint8_t[getPinCount(target_arduino_type)];
    memset(pin_set_modes, PIN_INFO_NONE, getPinCount(target_arduino_type));

    pin_output_values = new uint8_t[getPinCount(target_arduino_type)];
    memset(pin_output_values, PIN_WRITE_DO_NOT_CALL, getPinCount(target_arduino_type));

    pin_input_values = new uint8_t[getPinCount(target_arduino_type)];
    memset(pin_input_values, LOW, getPinCount(target_arduino_type));


    is_write_high = new bool[getPinCount(target_arduino_type)];
    memset(is_write_high, false, getPinCount(target_arduino_type));

    is_write_low = new bool[getPinCount(target_arduino_type)];
    memset(is_write_low, false, getPinCount(target_arduino_type));

}

void tearDownArduino()
{
    delete[] pin_set_modes;
    delete[] pin_output_values;
    delete[] pin_input_values;
    delete[] is_write_high;
    delete[] is_write_low;
}


BYTE getPinCount(ARDUINO_TYPE type)
{
    BYTE pin_count = 0;
    switch (type)
    {
        case ARDUINO_TYPE::UNO:
            pin_count = 14;
            break;

        default:
            break;
    }
    return pin_count;
}
